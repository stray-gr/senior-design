fn build_msg() {
    // NOTE: UUID strings are a max of 36 characters -> 36 bytes
    let mut pb_gen = micropb_gen::Generator::new();
    pb_gen
        .use_container_heapless()
        .configure(".Connect.device", micropb_gen::Config::new().max_bytes(36))
        .configure(".LWT.device", micropb_gen::Config::new().max_bytes(36))
        .configure(".SensorData.device", micropb_gen::Config::new().max_bytes(36))
        .compile_protos(
            &["msg.proto"], 
            "src/msg.rs",
        )
        .unwrap();
}

fn main() {
    embuild::espidf::sysenv::output();
    build_msg();
}
