use actix::prelude::*;

#[derive(Clone, Message)]
#[rtype(result = "()")]
pub struct DOMElement(pub String);

pub type Client = Recipient<DOMElement>;

#[derive(Clone, Message)]
#[rtype(result = "()")]
pub struct JoinBroadcast(pub Client);

#[derive(Clone, Message)]
#[rtype(result = "()")]
pub struct LeaveBroadcast(pub Client);
