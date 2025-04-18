# Team GR IoT Data Pipeline Template

## Design Diagram D0

| Connection | Protocol | Auth | Properties |
| ---------- | -------- | ---- | ---------- |
| A | SSL   | User/Password | Sensor data gets sent from each facility to the database |
| B | HTTPS | API Token | GroupMe chat bot reports device failures to a maintenance GroupMe |
| C | SSL   | User/Password | Queried sensor data gets streamed to the gRPC API |
| D | HTTPS | mTLS | Rows of queried sensor data get streamed to the API user |

```mermaid
flowchart LR
  f1[Facility 1]
  f2[Facility 2]
  fn[Facility n]
  db[(Postgresql Database)]
  api[gRPC Database API]
  user(((API User)))

  subgraph Input
    f1 ~~~ f2
    f2 -.- fn
  end

  subgraph Storage
    db
  end

  subgraph Output
    api <-- D --> user
  end

  Input -- A --> Storage
  Input -- B --> Output
  Storage <-- C --> Output
```

## Design Diagram D1

| Connection | Protocol | Auth | Properties |
| ---------- | -------- | ---- | ---------- |
| A | SSL   | User/Password | Sensor data gets sent from each facility to the database |
| B | HTTPS | API Token | GroupMe chat bot reports device failures to a maintenance GroupMe |
| C | SSL   | User/Password | Queried sensor data gets streamed to the gRPC API |
| D | HTTPS | mTLS | Rows of queried sensor data get streamed to the API user |

```mermaid
flowchart LR
  f1[Facility 1]
  f2[Facility 2]
  fn[Facility n]
  db[(Postgresql Data Schema)]
  facil[[Facility Table]]
  sensor[[Sensor Table]]
  api[gRPC Database API]
  user(((API User)))

  subgraph Input
    f1 ~~~ f2
    f2 -.- fn
  end

  subgraph Storage
    db --> facil
    db --> sensor
  end

  subgraph Output
    api <-- D --> user
  end

  Input -- A --> Storage
  Input -- B --> Output
  Storage <-- C --> Output
```

```mermaid
erDiagram
"Facility Table" {
  serial **facility_id**
  varchar(128) facility_name
}
"Sensor Table" {
  serial **entry_id**
  serial ***facility_id***
  varchar(64) device
  real temp
  real rh
  bigint epoch
}
```

## Design Diagram D1

### Facility Diagram

| Connection | Protocol | Auth | Properties |
| ---------- | -------- | ---- | ---------- |
| A | MQTTS     | User/Password | Sensor data gets sent from each facility to the database |
| B | MQTTS     | API Token | GroupMe chat bot reports device failures to a maintenance GroupMe |
| C | MQTTS     | User/Password | Queried sensor data gets streamed to the gRPC API |
| D | TLS       | mTLS | Rows of queried sensor data get streamed to the API user |
| E | SSL/HTTPS | mTLS | Rows of queried sensor data get streamed to the API user |

```mermaid
flowchart
  s[DHT22 Sensor]
  e[ESP32]
  mqtt[(Mosquitto MQTT Broker)]
  redis[(Redis)]
  clock[Clock Microservice]
  batch[Batch-Router Microservice]
  sink@{ shape: circle, label: "" }

 
  subgraph Devices
    s -- Digital Pin --> e
  end


  Devices <-- A --> mqtt
  clock -- B --> mqtt
  batch <-- C --> mqtt
  batch <-- D --> redis
  batch -- E --> sink
```

### Facility Diagram