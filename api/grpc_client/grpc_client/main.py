import api_pb2 as api_pb
import api_pb2_grpc as api_pb_grpc
import config as config
import google.protobuf.empty_pb2 as empty
import grpc

from typing import List

def load_cert(cert_path: str) -> bytes:
    with open(cert_path, 'rb') as cert:
        return cert.read()

def print_rows(stub: api_pb_grpc.QueryStub) -> None:
    rows: List[api_pb.SensorRows] = stub.GetSensorRows(empty.Empty())
    for r in rows:
        print(f'{r.entry_id}')

def run_success() -> None: 
    channel_mtls = grpc.ssl_channel_credentials(
        root_certificates=load_cert(config.CA_CRT),
        private_key=load_cert(config.VALID_API_KEY),
        certificate_chain=load_cert(config.VALID_API_CRT)
    )
    with grpc.secure_channel(config.URI, channel_mtls) as channel:
        stub = api_pb_grpc.QueryStub(channel)
        print_rows(stub)

def run_fail() -> None: 
    channel_mtls = grpc.ssl_channel_credentials(
        root_certificates=load_cert(config.CA_CRT),
        private_key=load_cert(config.INVALID_API_KEY),
        certificate_chain=load_cert(config.INVALID_API_CRT)
    )
    with grpc.secure_channel(config.URI, channel_mtls) as channel:
        stub = api_pb_grpc.QueryStub(channel)
        print_rows(stub)

if __name__ == '__main__':
    run_success()

    try:
        run_fail()
    except:
        print('Tests passed')
    else:
        print('Tests failed, client with bad certs still connected')
