// Copyright(c) 2022-present, Salvatore Cuzzilla (Swisscom AG)
// Distributed under the MIT License (http://opensource.org/licenses/MIT)


// mdt-dialout-collector Library headers
#include "core/mdt_dialout_core.h"


// Global visibility to be able to signal the refresh --> CSV from main
std::unordered_map<std::string, std::vector<std::string>> label_map;

bool CustomSocketMutator::bindtodevice_socket_mutator(int fd)
{
    int type;
    socklen_t len = sizeof(type);

    std::string iface = main_cfg_parameters.at("iface");

    if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len) != 0) {
        //std::cout << "Issues with getting the iface type ..." << "\n";
    }

    if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE,
        iface.c_str(), strlen(iface.c_str())) != 0) {
        //std::cout << "Issues with iface binding for ..." << "\n";
    }

    return true;
}

bool custom_socket_mutator_fd(int fd, grpc_socket_mutator *mutator0) {
    CustomSocketMutator *csm = (CustomSocketMutator *)mutator0;
    return csm->bindtodevice_socket_mutator(fd);
}

#define GPR_ICMP(a, b) ((a) < (b) ? -1 : ((a) > (b) ? 1 : 0))
int custom_socket_compare(grpc_socket_mutator *mutator1,
    grpc_socket_mutator *mutator2)
{
    return GPR_ICMP(mutator1, mutator2);
}

void custom_socket_destroy(grpc_socket_mutator *mutator)
{
    gpr_free(mutator);
}

const grpc_socket_mutator_vtable
    custom_socket_mutator_vtable = grpc_socket_mutator_vtable{
        custom_socket_mutator_fd,
        custom_socket_compare,
        custom_socket_destroy,
        nullptr};

void ServerBuilderOptionImpl::UpdateArguments(
    grpc::ChannelArguments *custom_args) {
        CustomSocketMutator *csm_ = new CustomSocketMutator();
        custom_args->SetSocketMutator(csm_);
}

CustomSocketMutator::CustomSocketMutator() {
    multi_logger->debug("constructor: CustomSocketMutator()");
    grpc_socket_mutator_init(this, &custom_socket_mutator_vtable);
}

void Srv::CiscoBind(std::string cisco_srv_socket)
{
    grpc::ServerBuilder cisco_builder;
    cisco_builder.RegisterService(&cisco_service_);
    // --- Required for socket manipulation ---
    std::unique_ptr<ServerBuilderOptionImpl>
        csbo(new ServerBuilderOptionImpl());
    cisco_builder.SetOption(std::move(csbo));
    // --- Required for socket manipulation ---
    cisco_builder.AddListeningPort(cisco_srv_socket,
        grpc::InsecureServerCredentials());
    cisco_cq_ = cisco_builder.AddCompletionQueue();
    cisco_server_ = cisco_builder.BuildAndStart();

    Srv::CiscoFsmCtrl();
}

void Srv::JuniperBind(std::string juniper_srv_socket)
{
    grpc::ServerBuilder juniper_builder;
    juniper_builder.RegisterService(&juniper_service_);
    // --- Required for socket manipulation ---
    std::unique_ptr<ServerBuilderOptionImpl>
        jsbo(new ServerBuilderOptionImpl());
    juniper_builder.SetOption(std::move(jsbo));
    // --- Required for socket manipulation ---
    juniper_builder.AddListeningPort(juniper_srv_socket,
        grpc::InsecureServerCredentials());
    juniper_cq_ = juniper_builder.AddCompletionQueue();
    juniper_server_ = juniper_builder.BuildAndStart();

    Srv::JuniperFsmCtrl();
}

void Srv::HuaweiBind(std::string huawei_srv_socket)
{
    grpc::ServerBuilder huawei_builder;
    huawei_builder.RegisterService(&huawei_service_);
    // --- Required for socket manipulation ---
    std::unique_ptr<ServerBuilderOptionImpl>
        hsbo(new ServerBuilderOptionImpl());
    huawei_builder.SetOption(std::move(hsbo));
    // --- Required for socket manipulation ---
    huawei_builder.AddListeningPort(huawei_srv_socket,
        grpc::InsecureServerCredentials());
    huawei_cq_ = huawei_builder.AddCompletionQueue();
    huawei_server_ = huawei_builder.BuildAndStart();

    Srv::HuaweiFsmCtrl();
}

void Srv::CiscoFsmCtrl()
{
    std::unique_ptr<DataManipulation> data_manipulation(
        new DataManipulation());
    std::unique_ptr<DataDelivery> data_delivery(
        new DataDelivery());
    std::unique_ptr<kafka::clients::KafkaProducer> producer(
        new kafka::clients::KafkaProducer(data_delivery->get_properties()));
    std::unique_ptr<cisco_telemetry::Telemetry> cisco_tlm(
        new cisco_telemetry::Telemetry());

    std::unique_ptr<Srv::CiscoStream> cisco_sstream(
        new Srv::CiscoStream(&cisco_service_, cisco_cq_.get()));
    cisco_sstream->Start(label_map, data_manipulation, data_delivery, producer,
        cisco_tlm);
    //int cisco_counter {0};
    void *cisco_tag {nullptr};
    bool cisco_ok {false};
    while (true) {
        //std::cout << "Cisco: " << cisco_counter << "\n";
        GPR_ASSERT(cisco_cq_->Next(&cisco_tag, &cisco_ok));
        //GPR_ASSERT(cisco_ok);
        if (cisco_ok == false) {
            multi_logger->warn("[CiscoFsmCtrl][grpc::CompletionQueue] "
                "unsuccessful event");
            continue;
        }
        static_cast<CiscoStream *>(cisco_tag)->Srv::CiscoStream::Start(
            label_map, data_manipulation, data_delivery, producer, cisco_tlm);
        //cisco_counter++;
    }
}

void Srv::JuniperFsmCtrl()
{
    std::unique_ptr<DataManipulation> data_manipulation(
        new DataManipulation());
    std::unique_ptr<DataDelivery> data_delivery(
        new DataDelivery());
    std::unique_ptr<kafka::clients::KafkaProducer> producer(
        new kafka::clients::KafkaProducer(data_delivery->get_properties()));
    std::unique_ptr<GnmiJuniperTelemetryHeaderExtension> juniper_tlm_hdr_ext(
        new GnmiJuniperTelemetryHeaderExtension());

    std::unique_ptr<Srv::JuniperStream> juniper_sstream(
        new Srv::JuniperStream(&juniper_service_, juniper_cq_.get()));
    juniper_sstream->Start(label_map, data_manipulation, data_delivery,
        producer, juniper_tlm_hdr_ext);
    //int juniper_counter {0};
    void *juniper_tag {nullptr};
    bool juniper_ok {false};
    while (true) {
        //std::cout << "Juniper: " << juniper_counter << "\n";
        GPR_ASSERT(juniper_cq_->Next(&juniper_tag, &juniper_ok));
        //GPR_ASSERT(juniper_ok);
        if (juniper_ok == false) {
            multi_logger->warn("[JuniperFsmCtrl][grpc::CompletionQueue] "
                "unsuccessful event");
            continue;
        }
        static_cast<JuniperStream *>(juniper_tag)->Srv::JuniperStream::Start(
            label_map, data_manipulation, data_delivery, producer,
            juniper_tlm_hdr_ext);
        //juniper_counter++;
    }
}

void Srv::HuaweiFsmCtrl()
{
    std::unique_ptr<DataManipulation> data_manipulation(
        new DataManipulation());
    std::unique_ptr<DataDelivery> data_delivery(
        new DataDelivery());
    std::unique_ptr<kafka::clients::KafkaProducer> producer(
        new kafka::clients::KafkaProducer(data_delivery->get_properties()));
    std::unique_ptr<huawei_telemetry::Telemetry> huawei_tlm(
        new huawei_telemetry::Telemetry());
    std::unique_ptr<openconfig_interfaces::Interfaces> oc_if(
        new openconfig_interfaces::Interfaces());

    std::unique_ptr<Srv::HuaweiStream> huawei_sstream(
        new Srv::HuaweiStream(&huawei_service_, huawei_cq_.get()));
    huawei_sstream->Start(label_map, data_manipulation, data_delivery,
        producer, huawei_tlm, oc_if);
    //int huawei_counter {0};
    void *huawei_tag {nullptr};
    bool huawei_ok {false};
    while (true) {
        //std::cout << "Huawei: " << huawei_counter << "\n";
        GPR_ASSERT(huawei_cq_->Next(&huawei_tag, &huawei_ok));
        //GPR_ASSERT(huawei_ok);
        if (huawei_ok == false) {
            multi_logger->warn("[HuaweiFsmCtrl][grpc::CompletionQueue] "
                "unsuccessful event");
            continue;
        }
        static_cast<HuaweiStream *>(huawei_tag)->Srv::HuaweiStream::Start(
            label_map, data_manipulation, data_delivery, producer,
            huawei_tlm, oc_if);
        //huawei_counter++;
    }
}

Srv::CiscoStream::CiscoStream(
    mdt_dialout::gRPCMdtDialout::AsyncService *cisco_service,
    grpc::ServerCompletionQueue *cisco_cq) :
        cisco_service_ {cisco_service},
        cisco_cq_ {cisco_cq},
        cisco_resp {&cisco_server_ctx},
        cisco_replies_sent {0},
        kCiscoMaxReplies
            {std::stoi(main_cfg_parameters.at("replies_cisco"))},
        cisco_stream_status {START}
{
    multi_logger->debug("constructor: CiscoStream()");
}

Srv::JuniperStream::JuniperStream(
    Subscriber::AsyncService *juniper_service,
    grpc::ServerCompletionQueue *juniper_cq) :
        juniper_service_ {juniper_service},
        juniper_cq_ {juniper_cq},
        juniper_resp {&juniper_server_ctx},
        juniper_replies_sent {0},
        kJuniperMaxReplies
            {std::stoi(main_cfg_parameters.at("replies_juniper"))},
        juniper_stream_status {START}
{
    multi_logger->debug("constructor: JuniperStream()");
}

Srv::HuaweiStream::HuaweiStream(
    huawei_dialout::gRPCDataservice::AsyncService *huawei_service,
    grpc::ServerCompletionQueue *huawei_cq) :
        huawei_service_ {huawei_service},
        huawei_cq_ {huawei_cq},
        huawei_resp {&huawei_server_ctx},
        huawei_replies_sent {0},
        kHuaweiMaxReplies
            {std::stoi(main_cfg_parameters.at("replies_huawei"))},
        huawei_stream_status {START}
{
    multi_logger->debug("constructor: HuaweiStream()");
}

void Srv::CiscoStream::Start(
    std::unordered_map<std::string,std::vector<std::string>> &label_map,
    std::unique_ptr<DataManipulation> &data_manipulation,
    std::unique_ptr<DataDelivery> &data_delivery,
    std::unique_ptr<kafka::clients::KafkaProducer> &producer,
    std::unique_ptr<cisco_telemetry::Telemetry> &cisco_tlm)
{
    // Initial stream_status set to START @constructor
    if (cisco_stream_status == START) {
        cisco_service_->RequestMdtDialout(
            &cisco_server_ctx,
            &cisco_resp,
            cisco_cq_,
            cisco_cq_,
            this);
        cisco_stream_status = FLOW;
    } else if (cisco_stream_status == FLOW) {
        multi_logger->debug("[CiscoStream::Start()] "
            "new Srv::CiscoStream()");
        Srv::CiscoStream *cisco_sstream =
            new Srv::CiscoStream(cisco_service_, cisco_cq_);
        cisco_sstream->Start(label_map, data_manipulation, data_delivery,
            producer, cisco_tlm);
        cisco_resp.Read(&cisco_stream, this);
        cisco_stream_status = PROCESSING;
        cisco_replies_sent++;
    } else if (cisco_stream_status == PROCESSING) {
        if (cisco_replies_sent == kCiscoMaxReplies) {
            multi_logger->debug("[CiscoStream::Start()] "
                "cisco_stream_status = END");
            cisco_stream_status = END;
            cisco_resp.Finish(grpc::Status::OK, this);
        } else {
            //  --- DEBUG ---
            //for (auto &e : label_map) {
            //    std::cout << e.first << " ---> "
            //    << "[" << e.second.at(0) << ","
            //    << e.second.at(1) << "]\n";
            //}
            //  --- DEBUG ---
            bool parsing_str {false};
            // From the network
            std::string stream_data_in;
            // After data enrichment
            std::string stream_data_out;
            const std::string _peer = cisco_server_ctx.peer();
            // select exclusively the IP addr from peer
            unsigned start_delim = (_peer.find_first_of(":") + 1);
            unsigned stop_delim = _peer.find_last_of(":");
            std::string peer = _peer.substr(
                start_delim, (stop_delim - start_delim));
            // the key-word "this" is used as a unique TAG
            cisco_resp.Read(&cisco_stream, this);
            // returns true for GPB-KV & GPB, false for JSON
            // (from protobuf libs)
            parsing_str = cisco_tlm->ParseFromString(cisco_stream.data());

            stream_data_in = cisco_stream.data();

            // Handling empty data
            if (stream_data_in.empty() == true) {
                multi_logger->info("[CiscoStream::Start()] {} handling empty "
                    "data", peer);
            // Handling GPB-KV
            } else if (cisco_tlm->data_gpbkv().empty() == false &&
                parsing_str == true) {
                multi_logger->info("[CiscoStream::Start()] {} handling GPB-KV "
                    "data", peer);
                // std::string:compare returns 0 when the compared strings are
                // matching
                if (data_manipulation_cfg_parameters.at(
                    "enable_cisco_gpbkv2json").compare("true") == 0) {
                    if (data_manipulation->CiscoGpbkv2Json(cisco_tlm,
                        stream_data_in) == true) {
                        multi_logger->info("[CiscoStream::Start()] {} "
                            "enable_cisco_gpbkv2json, data-normalization "
                            "successful", peer);
                        // Data enrichment with label (node_id/platform_id)
                        if (data_manipulation_cfg_parameters.at(
                            "enable_label_encode_as_map").compare("true")
                                == 0 || data_manipulation_cfg_parameters.at(
                            "enable_label_encode_as_map_ptm").compare("true")
                                == 0) {
                            if (data_manipulation->AppendLabelMap(
                                label_map,
                                peer,
                                stream_data_in,
                                stream_data_out) == true) {
                                data_delivery->AsyncKafkaProducer(
                                    producer,
                                    peer,
                                    stream_data_out);
                            }
                        } else {
                            stream_data_out = stream_data_in;
                            data_delivery->AsyncKafkaProducer(
                                producer,
                                peer,
                                stream_data_out);
                        }
                    } else {
                        multi_logger->error("[CiscoStream::Start()] {} "
                            "enable_cisco_gpbkv2json, data-normalization "
                            "failure", peer);
                    }
                } else if (data_manipulation_cfg_parameters.at(
                    "enable_cisco_message_to_json_string").compare(
                    "true") == 0) {
                    // MessageToJson is working directly on the PROTO-Obj
                    stream_data_in.clear();
                    google::protobuf::util::JsonPrintOptions opt;
                    opt.add_whitespace = true;
                    google::protobuf::util::MessageToJsonString(
                        *cisco_tlm,
                        &stream_data_in,
                        opt);
                    // Data enrichment with label (node_id/platform_id)
                    if (data_manipulation_cfg_parameters.at(
                        "enable_label_encode_as_map").compare("true") == 0 ||
                        data_manipulation_cfg_parameters.at(
                        "enable_label_encode_as_map_ptm").compare("true")
                            == 0) {
                        if (data_manipulation->AppendLabelMap(
                            label_map,
                            peer,
                            stream_data_in,
                            stream_data_out) == true) {
                            data_delivery->AsyncKafkaProducer(
                                producer,
                                peer,
                                stream_data_out);
                        }
                    } else {
                        stream_data_out = stream_data_in;
                        data_delivery->AsyncKafkaProducer(
                            producer,
                            peer,
                            stream_data_out);
                    }
                } else {
                    // Use Case: both data manipulation funcs set to false:
                    // TBD: at the meoment simply alert
                    multi_logger->error("[CiscoStream::Start()] {} "
                        "general data-manipulation failure "
                        "conflicting manipulation functions", peer);
                }

            // Handling GPB
            } else if (cisco_tlm->has_data_gpb() == true &&
                parsing_str == true) {
                multi_logger->info("[CiscoStream::Start()] {} handling GPB "
                    "data", peer);
                // Data enrichment with label (node_id/platform_id)
                if (data_manipulation_cfg_parameters.at(
                    "enable_label_encode_as_map").compare("true") == 0 ||
                    data_manipulation_cfg_parameters.at(
                    "enable_label_encode_as_map_ptm").compare("true") == 0) {
                    if (data_manipulation->AppendLabelMap(
                        label_map,
                        peer,
                        stream_data_in,
                        stream_data_out) == true) {
                        data_delivery->AsyncKafkaProducer(
                            producer,
                            peer,
                            stream_data_out);
                    }
                } else {
                    stream_data_out = stream_data_in;
                    data_delivery->AsyncKafkaProducer(
                        producer,
                        peer,
                        stream_data_out);
                }
            // Handling JSON string
            } else if (parsing_str == false) {
                multi_logger->info("[CiscoStream::Start()] {} handling JSON "
                    "data", peer);
                // Data enrichment with label (node_id/platform_id)
                if (data_manipulation_cfg_parameters.at(
                    "enable_label_encode_as_map").compare("true") == 0 ||
                    data_manipulation_cfg_parameters.at(
                    "enable_label_encode_as_map_ptm").compare("true") == 0) {
                    if (data_manipulation->AppendLabelMap(
                        label_map,
                        peer,
                        stream_data_in,
                        stream_data_out) == true) {
                        data_delivery->AsyncKafkaProducer(
                            producer,
                            peer,
                            stream_data_out);
                    }
                } else {
                    stream_data_out = stream_data_in;
                    data_delivery->AsyncKafkaProducer(
                        producer,
                        peer,
                        stream_data_out);
                }
            }
            cisco_stream_status = PROCESSING;
            cisco_replies_sent++;
        }
    } else {
        multi_logger->debug("[CiscoStream::Start()] "
            "GPR_ASSERT(cisco_stream_status == END)");
        GPR_ASSERT(cisco_stream_status == END);
        delete this;
    }
}

void Srv::JuniperStream::Start(
    std::unordered_map<std::string,std::vector<std::string>> &label_map,
    std::unique_ptr<DataManipulation> &data_manipulation,
    std::unique_ptr<DataDelivery> &data_delivery,
    std::unique_ptr<kafka::clients::KafkaProducer> &producer,
    std::unique_ptr<GnmiJuniperTelemetryHeaderExtension> &juniper_tlm_hdr_ext)
{
    // Initial stream_status set to START @constructor
    if (juniper_stream_status == START) {
        juniper_service_->RequestDialOutSubscriber(
            &juniper_server_ctx,
            &juniper_resp,
            juniper_cq_,
            juniper_cq_,
            this);
        juniper_stream_status = FLOW;
    } else if (juniper_stream_status == FLOW) {
        multi_logger->debug("[JuniperStream::Start()] "
            "new Srv::JuniperStream()");
        Srv::JuniperStream *juniper_sstream =
            new Srv::JuniperStream(juniper_service_, juniper_cq_);
        juniper_sstream->Start(label_map, data_manipulation, data_delivery,
            producer, juniper_tlm_hdr_ext);
        juniper_resp.Read(&juniper_stream, this);
        juniper_stream_status = PROCESSING;
        juniper_replies_sent++;
    } else if (juniper_stream_status == PROCESSING) {
        if (juniper_replies_sent == kJuniperMaxReplies) {
            multi_logger->debug("[JuniperStream::Start()] "
                "juniper_stream_status = END");
            juniper_stream_status = END;
            juniper_resp.Finish(grpc::Status::OK, this);
        } else {
            // From the network
            std::string stream_data_in;
            // After data enrichment
            std::string stream_data_out;
            std::string json_str_out;
            const std::string _peer = juniper_server_ctx.peer();
            // select exclusively the IP addr from peer
            unsigned start_delim = (_peer.find_first_of(":") + 1);
            unsigned stop_delim = _peer.find_last_of(":");
            std::string peer = _peer.substr(
                start_delim, (stop_delim - start_delim));
            Json::Value root;

            // the key-word "this" is used as a unique TAG
            juniper_resp.Read(&juniper_stream, this);

            if (data_manipulation->JuniperExtension(juniper_stream,
                juniper_tlm_hdr_ext, root) == true &&
                data_manipulation->JuniperUpdate(juniper_stream, json_str_out,
                    root) == true) {
                    multi_logger->info("[JuniperStream::Start()] {} "
                        "JuniperExtension, parsing successful", peer);
            } else {
                    multi_logger->error("[JuniperStream::Start()] {} "
                        "JuniperExtension, parsing failure", peer);
            }

            // Data enrichment with label (node_id/platform_id)
            stream_data_in = json_str_out;

            if (data_manipulation_cfg_parameters.at(
                "enable_label_encode_as_map").compare("true") == 0 ||
                data_manipulation_cfg_parameters.at(
                "enable_label_encode_as_map_ptm").compare("true") == 0) {
                if (data_manipulation->AppendLabelMap(
                    label_map,
                    peer,
                    stream_data_in,
                    stream_data_out) == true) {
                    data_delivery->AsyncKafkaProducer(
                        producer,
                        peer,
                        stream_data_out);
                }
            } else {
                stream_data_out = json_str_out;
                data_delivery->AsyncKafkaProducer(
                    producer,
                    peer,
                    stream_data_out);
            }

            juniper_stream_status = PROCESSING;
            juniper_replies_sent++;
        }
    } else {
        multi_logger->debug("[JuniperStream::Start()] "
            "GPR_ASSERT(juniper_stream_status == END)");
        GPR_ASSERT(juniper_stream_status == END);
        delete this;
    }
}

void Srv::HuaweiStream::Start(
    std::unordered_map<std::string,std::vector<std::string>> &label_map,
    std::unique_ptr<DataManipulation> &data_manipulation,
    std::unique_ptr<DataDelivery> &data_delivery,
    std::unique_ptr<kafka::clients::KafkaProducer> &producer,
    std::unique_ptr<huawei_telemetry::Telemetry> &huawei_tlm,
    std::unique_ptr<openconfig_interfaces::Interfaces> &oc_if)
{
    // Initial stream_status set to START @constructor
    if (huawei_stream_status == START) {
        huawei_service_->RequestdataPublish(
            &huawei_server_ctx,
            &huawei_resp,
            huawei_cq_,
            huawei_cq_,
            this);
        huawei_stream_status = FLOW;
    } else if (huawei_stream_status == FLOW) {
        multi_logger->debug("[HuaweiStream::Start()] "
            "new Srv::HuaweiStream()");
        Srv::HuaweiStream *huawei_sstream =
            new Srv::HuaweiStream(huawei_service_, huawei_cq_);
        huawei_sstream->Start(label_map, data_manipulation, data_delivery,
            producer, huawei_tlm, oc_if);
        huawei_resp.Read(&huawei_stream, this);
        huawei_stream_status = PROCESSING;
        huawei_replies_sent++;
    } else if (huawei_stream_status == PROCESSING) {
        if (huawei_replies_sent == kHuaweiMaxReplies) {
            multi_logger->debug("[HuaweiStream::Start()] "
                "huawei_stream_status = END");
            huawei_stream_status = END;
            huawei_resp.Finish(grpc::Status::OK, this);
        } else {
            bool parsing_str {false};
            // From the network
            std::string stream_data_in;
            // Afetr data enrichment
            std::string stream_data_out;
            std::string json_str_out;
            const std::string _peer = huawei_server_ctx.peer();
            // select exclusively the IP addr from peer
            unsigned start_delim = (_peer.find_first_of(":") + 1);
            unsigned stop_delim = _peer.find_last_of(":");
            std::string peer = _peer.substr(
                start_delim, (stop_delim - start_delim));

            huawei_resp.Read(&huawei_stream, this);
            parsing_str = huawei_tlm->ParseFromString(huawei_stream.data());

            stream_data_in = huawei_stream.data();

            // Handling empty data
            if (stream_data_in.empty() == true) {
                multi_logger->info("[HuaweiStream::Start()] {} handling empty "
                    "data", peer);
            }

            // Handling GPB
            else {
                // Handling OpenConfig interfaces
                if (huawei_tlm->has_data_gpb() == true &&
                    parsing_str == true &&
                    huawei_tlm->proto_path().compare(
                        "openconfig_interfaces.Interfaces") == 0) {
                    multi_logger->info("[HuaweiStream::Start()] {} handling "
                        "GPB data", peer);

                    if (data_manipulation->HuaweiGpbOpenconfigInterface(
                        huawei_tlm, oc_if, json_str_out) == true) {
                            multi_logger->info("[HuaweiStream::Start()] {} "
                                "HuaweiGpbOpenconfigInterface, "
                                "parsing successful", peer);
                    } else {
                        multi_logger->error("[HuaweiStream::Start()] {}"
                            "HuaweiGpbOpenconfigInterface, "
                            "parsing failure", peer);
                    }

                    // Data enrichment with label (node_id/platform_id)
                    stream_data_in = json_str_out;
                    if (data_manipulation_cfg_parameters.at(
                        "enable_label_encode_as_map").compare("true") == 0 ||
                        data_manipulation_cfg_parameters.at(
                        "enable_label_encode_as_map_ptm").compare("true")
                            == 0) {
                        if (data_manipulation->AppendLabelMap(
                            label_map,
                            peer,
                            stream_data_in,
                            stream_data_out) == true) {
                            data_delivery->
                                AsyncKafkaProducer(
                                    producer,
                                    peer,
                                    stream_data_out);
                        }
                    } else {
                        stream_data_out = json_str_out;
                        data_delivery->AsyncKafkaProducer(
                            producer,
                            peer,
                            stream_data_out);
                    }
                }
            }

            stream_data_in = huawei_stream.data_json();

            // Handling empty data_json
            if (stream_data_in.empty() == true) {
                multi_logger->info("[HuaweiStream::Start()] {} handling empty "
                    "data_json", peer);
            }
            // Handling JSON string
            else {
                // ---
                multi_logger->info("[HuaweiStream::Start()] {} handling JSON "
                    "data_json", peer);

                // Data enrichment with label (node_id/platform_id)
                if (data_manipulation_cfg_parameters.at(
                    "enable_label_encode_as_map").compare("true") == 0 ||
                    data_manipulation_cfg_parameters.at(
                    "enable_label_encode_as_map_ptm").compare("true") == 0) {
                    if (data_manipulation->AppendLabelMap(
                        label_map,
                        peer,
                        stream_data_in,
                        stream_data_out) == true) {
                        data_delivery->AsyncKafkaProducer(
                            producer,
                            peer,
                            stream_data_out);
                    }
                } else {
                    stream_data_out = stream_data_in;
                    data_delivery->AsyncKafkaProducer(
                        producer,
                        peer,
                        stream_data_out);
                }
            }

            huawei_stream_status = PROCESSING;
            huawei_replies_sent++;
        }
    } else {
        multi_logger->debug("[HuaweiStream::Start()] "
            "GPR_ASSERT(huawei_stream_status == END)");
        GPR_ASSERT(huawei_stream_status == END);
        delete this;
    }
}

