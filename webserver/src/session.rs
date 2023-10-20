use actix::{fut, prelude::*};
use actix_web_actors::ws;
use crate::{
    messages::{DOMElement, JoinBroadcast},
    server::BroadcastServer,
};

#[derive(Default)]
pub struct Session;

impl Session {
    pub fn join_broadcast(&mut self, ctx: &mut ws::WebsocketContext<Self>) {
        let join_req = JoinBroadcast(ctx.address().recipient());
        BroadcastServer::from_registry()
            .send(join_req) 
            .into_actor(self) 
            .then(|_, _, _| {
                fut::ready(())
            })
            .wait(ctx);
    }
}

impl Actor for Session {
    type Context = ws::WebsocketContext<Self>;

    fn started(&mut self, ctx: &mut Self::Context) {
        self.join_broadcast(ctx);
    }
}

impl Handler<DOMElement> for Session {
    type Result = ();

    fn handle(&mut self, msg: DOMElement, ctx: &mut Self::Context) {
        ctx.text(msg.0);
    }
}

impl StreamHandler<Result<ws::Message, ws::ProtocolError>> for Session {
    fn handle(&mut self, msg: Result<ws::Message, ws::ProtocolError>, ctx: &mut Self::Context) {
        match msg {
            Err(e) => {
                log::error!("{e:?}");
                ctx.stop();
                return;
            }
            _ => (),
        };

        self.join_broadcast(ctx);
    }
}