use actix::prelude::*;
use actix_broker::BrokerSubscribe;
use crate::messages::{Client, DOMElement, JoinBroadcast};
use std::{
    thread,
    time::Duration,
};

const THINGS: [&str; 2] = ["Hello", "World"];

#[derive(Default)]
pub struct BroadcastServer;

impl BroadcastServer {
    fn broadcast_to_client(&mut self, client: Client) {
        thread::spawn(move || loop {
            for t in THINGS {
                if client.connected() {
                    let target_div: String = format!(r#"
                        <div id="target" hx-swap-oob="true">
                            {t}
                        </div>
                    "#);
                    match client.try_send(DOMElement(target_div)) {
                        Err(e) => {
                            log::error!("{e:?}");
                            return;
                        }
                        _ => (),
                    }
                    thread::sleep(Duration::from_secs(1));
                } else {
                    return;
                }
            }
        });
    }
}

impl Actor for BroadcastServer {
    type Context = Context<Self>;
    fn started(&mut self, ctx: &mut Self::Context) {
        self.subscribe_system_async::<JoinBroadcast>(ctx);
    }
}

impl Handler<JoinBroadcast> for BroadcastServer {
    type Result = ();

    fn handle(&mut self, msg: JoinBroadcast, _ctx: &mut Self::Context) {
        let JoinBroadcast(client) = msg;
        self.broadcast_to_client(client);
    }
}

impl SystemService for BroadcastServer {}
impl Supervised for BroadcastServer {}