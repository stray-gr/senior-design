# Team GR IoT Data Pipeline Template

## Team Members
- Gabriel Rodriguez-Padilla
  - Major: Computer Science
  - Email: rodrigg2@mail.uc.edu

## External Advisor
- Peter Kroeger
  - Email: peter14mail@gmail.com

## Project Area
- IoT Data Aggregation

## Project Abstract
The purpose of this project is to devise a data pipeline template that can used by other developers to create a data pipeline in house that meets their arbitrary requirements. For the purposes of this project, this data pipeline template will demonstrate how to collect atmospheric data from the interior of multiple facilities as an example exercise. Collection of such data will be accomplished by sending real time atmospheric data from a network of IoT devices to a mircoservice responsible for batching and routing the collected data for a given facility. For each batch of atmospheric data, this *batch-router* will route the data to a central SQL database. Note that this database will be used to store data from other facilities as well. Additionally, the *batch-router* will send each batch of device failures (delineated by a device suddenly disconnecting) to a GroupMe chat containing maintenance personnel via a chat bot. Lastly, there will be a headless gRPC API that authorized users can use to query batches of data from the database. The end goal is for this template to be affordable, extensible, and easy to implement by others.

## Inadequacy of Current Solutions
One of the main motivations of this project is to showcase the benefits of creating data pipelines in-house. A notable amount of organizations and companies use proprietary data acquisition hardware they bought from vendors for a high cost. As a result, this hardware is typically closed-source and can be difficult to extend and modify. Data aggregation solutions can also have the same issue with extensibility and price. Whether a solution be more affordable and difficult to extend, or extensible and expensive to use. Hopefully, this project will show that pipelines made in-house don’t have extensibility issues when implemented properly. Completing this project must also be done cost effectively to further demonstrate the benefits of pipelines made in-house.  

Another motivation of this project is to showcase new technology that can be used to improve the safety and efficiency of data pipelines. For example, newer programming languages such as Rust and Elixir can be used to improve the security and robustness of software running in the pipeline. Lastly, the world of embedded electronics has evolved since I last worked with such devices. Newer and more capable devices could lead to solutions being created with less time and effort. This project will highlight whether or not the "hype" behind this emerging technology is really worth it. 
