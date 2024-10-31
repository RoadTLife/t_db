#ifndef SRC_SERVER_CONFIG_H
#define SRC_SERVER_CONFIG_H

#include <atomic>
#include <string>

namespace tdb {

struct BasicConfigs {
    std::string db_dir = "./tdb_db";  // db
    int thread_limit = 0;                // number of threads, for both rpc and http
    int subprocess_max_idle_seconds = 600;
    // address and ssl
    std::string bind_host = "0.0.0.0";
    bool enable_ssl = false;
    std::string server_key_file;
    std::string server_cert_file;
    // http
    uint16_t http_port = 7071;
    std::string http_web_dir = "./resource";
    bool http_disable_auth = false;
    // rpc & ha
    bool enable_rpc = false;
    uint16_t rpc_port = 9091;
    bool use_pthread = false;
    bool enable_ha = false;
    std::string ha_conf;
    std::string ha_log_dir;
    int ha_election_timeout_ms = 500;           // election time out in 0.5s
    int ha_snapshot_interval_s = 7 * 24 * 3600;     // snapshot every 24 hours
    int ha_heartbeat_interval_ms = 1000;           // send heartbeat every 1 sec
    int ha_node_offline_ms = 1200000;   // node will be marked as offline after 20 min
    int ha_node_remove_ms = 600000;  // node will be removed from node list after 10 min
    int ha_node_join_group_s = 10;  // node will join group in 10 s
    int ha_bootstrap_role = 0;
    bool ha_is_witness = false;    // node is witness or not
    bool ha_enable_witness_to_leader = false;  // enable witness to leader or not
    std::string ha_first_snapshot_start_time;  // first snapshot start time
                                                    // whose format is "HH:MM:SS",
                                                    // and the default value is ""
                                                    // indicating a random time.
    bool is_cypher_v2 = true;

    // log
    int verbose = 1;
    std::string log_dir;
    size_t max_log_file_size_mb = 256;
    size_t max_n_log_files = 16;
    size_t audit_log_expire = 0;
    std::string audit_log_dir = "./audit_log";
    std::string backup_log_dir = "./binlog";
    std::string snapshot_dir = "./snapshot_log";
    size_t max_backup_log_file_size = (size_t)1 << 30;
    // token time
    bool unlimited_token = false;
    // reset admin password
    bool reset_admin_password = false;
    // vertex and edge count
    bool enable_realtime_count = true;
    // bolt
    int bolt_port = 0;
    int bolt_io_thread_num = 1;
    // default disable plugin load/delete
    bool enable_plugin = false;
};


// config for a TGraph instance
struct GlobalConfig : public BasicConfigs {
    // modifiable
    std::atomic<bool> durable{false};
    std::atomic<bool> txn_optimistic{false};
    std::atomic<bool> enable_audit_log{false};
    std::atomic<bool> enable_ip_check{false};
    std::atomic<bool> enable_backup_log{false};

    [[nodiscard]] std::string FormatAsString(size_t heading_space = 2) const;
    static int PrintVersion(std::string &config_file, std::string &cmd, int *argc, char ***argv);
    virtual void InitConfig(std::string &cmd);

};

}

#endif