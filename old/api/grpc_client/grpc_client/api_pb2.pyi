from google.protobuf import empty_pb2 as _empty_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class SensorRows(_message.Message):
    __slots__ = ("entry_id", "facility_id", "device", "temp", "rh", "epoch")
    ENTRY_ID_FIELD_NUMBER: _ClassVar[int]
    FACILITY_ID_FIELD_NUMBER: _ClassVar[int]
    DEVICE_FIELD_NUMBER: _ClassVar[int]
    TEMP_FIELD_NUMBER: _ClassVar[int]
    RH_FIELD_NUMBER: _ClassVar[int]
    EPOCH_FIELD_NUMBER: _ClassVar[int]
    entry_id: int
    facility_id: int
    device: str
    temp: int
    rh: float
    epoch: int
    def __init__(self, entry_id: _Optional[int] = ..., facility_id: _Optional[int] = ..., device: _Optional[str] = ..., temp: _Optional[int] = ..., rh: _Optional[float] = ..., epoch: _Optional[int] = ...) -> None: ...
