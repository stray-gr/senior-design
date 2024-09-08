# Team GR

## Team Members
- Gabriel Rodriguez-Padilla
  - Major: Computer Science
  - Email: rodrigg2@mail.uc.edu

## External Advisor
- TBD
  - Email: TBD

## Project Area
- IoT Data Aggregation

## Project Abstract
Currently, the focus of this IoT Data Aggregation project will be collecting atmospheric data from the interior of multiple facillities. This will be accomplished by sending real time atmospheric data from a network of IoT devices to a local (facility-specific) server running on a laptop or Raspberry Pi. The server will then aggregate the collected data and send each batch to a central SQL database. Note that this database will be used to store data from other facilities as well. Additionally, there will be a headless web API that authorized users can use to query batches of data from the database.

## Inadequacy of Current Solutions
One of the main motivations of this project is to showcase the benefits of creating data pipelines in-house. A notable amount of organizations and companies use data acquisition hardware they bought externally from vendors such as National Instruments. However, this hardware is typically closed-source and can be difficult to extend and modify. Data aggregation solutions can also have the same issue with extensibility. This is especially true for Microsoft Power Apps, which are rather limited in capability from my experience. Hopefully, this project will show that pipelines made in-house don’t have extensibility issues when implemented properly. Completing this project quickly and cost effectively would also help strengthen the benefits of pipelines made in-house.  

Another motivation of this project is to showcase new technology that can be used to improve the safety and efficiency of data pipelines. For example, newer programming languages such as Rust and Elixir can be used to improve the security and robustness of software running in the pipeline. Lastly, the world of embedded electronics has evolved since I last worked with such devices. Newer and more capable devices could lead to solutions being created with less time and effort.
