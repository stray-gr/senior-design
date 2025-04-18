#[derive(Debug, PartialEq, Clone)]
pub struct Connect {
    pub r#device: ::micropb::heapless::String<36>,
}
impl ::core::default::Default for Connect {
    fn default() -> Self {
        Self {
            r#device: ::core::default::Default::default(),
        }
    }
}
impl Connect {}
impl ::micropb::MessageDecode for Connect {
    fn decode<IMPL_MICROPB_READ: ::micropb::PbRead>(
        &mut self,
        decoder: &mut ::micropb::PbDecoder<IMPL_MICROPB_READ>,
        len: usize,
    ) -> Result<(), ::micropb::DecodeError<IMPL_MICROPB_READ::Error>> {
        use ::micropb::{PbVec, PbMap, PbString, FieldDecode};
        let before = decoder.bytes_read();
        while decoder.bytes_read() - before < len {
            let tag = decoder.decode_tag()?;
            match tag.field_num() {
                0 => return Err(::micropb::DecodeError::ZeroField),
                1u32 => {
                    let mut_ref = &mut self.r#device;
                    {
                        decoder.decode_string(mut_ref, ::micropb::Presence::Implicit)?;
                    };
                }
                _ => {
                    decoder.skip_wire_value(tag.wire_type())?;
                }
            }
        }
        Ok(())
    }
}
impl ::micropb::MessageEncode for Connect {
    fn encode<IMPL_MICROPB_WRITE: ::micropb::PbWrite>(
        &self,
        encoder: &mut ::micropb::PbEncoder<IMPL_MICROPB_WRITE>,
    ) -> Result<(), IMPL_MICROPB_WRITE::Error> {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        {
            let val_ref = &self.r#device;
            if !val_ref.is_empty() {
                encoder.encode_varint32(10u32)?;
                encoder.encode_string(val_ref)?;
            }
        }
        Ok(())
    }
    fn compute_size(&self) -> usize {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        let mut size = 0;
        {
            let val_ref = &self.r#device;
            if !val_ref.is_empty() {
                size += 1usize + ::micropb::size::sizeof_len_record(val_ref.len());
            }
        }
        size
    }
}
#[derive(Debug, PartialEq, Clone)]
pub struct LWT {
    pub r#device: ::micropb::heapless::String<36>,
    pub r#delay: i64,
}
impl ::core::default::Default for LWT {
    fn default() -> Self {
        Self {
            r#device: ::core::default::Default::default(),
            r#delay: ::core::default::Default::default(),
        }
    }
}
impl LWT {}
impl ::micropb::MessageDecode for LWT {
    fn decode<IMPL_MICROPB_READ: ::micropb::PbRead>(
        &mut self,
        decoder: &mut ::micropb::PbDecoder<IMPL_MICROPB_READ>,
        len: usize,
    ) -> Result<(), ::micropb::DecodeError<IMPL_MICROPB_READ::Error>> {
        use ::micropb::{PbVec, PbMap, PbString, FieldDecode};
        let before = decoder.bytes_read();
        while decoder.bytes_read() - before < len {
            let tag = decoder.decode_tag()?;
            match tag.field_num() {
                0 => return Err(::micropb::DecodeError::ZeroField),
                1u32 => {
                    let mut_ref = &mut self.r#device;
                    {
                        decoder.decode_string(mut_ref, ::micropb::Presence::Implicit)?;
                    };
                }
                2u32 => {
                    let mut_ref = &mut self.r#delay;
                    {
                        let val = decoder.decode_int64()?;
                        let val_ref = &val;
                        if *val_ref != 0 {
                            *mut_ref = val as _;
                        }
                    };
                }
                _ => {
                    decoder.skip_wire_value(tag.wire_type())?;
                }
            }
        }
        Ok(())
    }
}
impl ::micropb::MessageEncode for LWT {
    fn encode<IMPL_MICROPB_WRITE: ::micropb::PbWrite>(
        &self,
        encoder: &mut ::micropb::PbEncoder<IMPL_MICROPB_WRITE>,
    ) -> Result<(), IMPL_MICROPB_WRITE::Error> {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        {
            let val_ref = &self.r#device;
            if !val_ref.is_empty() {
                encoder.encode_varint32(10u32)?;
                encoder.encode_string(val_ref)?;
            }
        }
        {
            let val_ref = &self.r#delay;
            if *val_ref != 0 {
                encoder.encode_varint32(16u32)?;
                encoder.encode_int64(*val_ref as _)?;
            }
        }
        Ok(())
    }
    fn compute_size(&self) -> usize {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        let mut size = 0;
        {
            let val_ref = &self.r#device;
            if !val_ref.is_empty() {
                size += 1usize + ::micropb::size::sizeof_len_record(val_ref.len());
            }
        }
        {
            let val_ref = &self.r#delay;
            if *val_ref != 0 {
                size += 1usize + ::micropb::size::sizeof_int64(*val_ref as _);
            }
        }
        size
    }
}
#[derive(Debug, PartialEq, Clone)]
pub struct SensorData {
    pub r#device: ::micropb::heapless::String<36>,
    pub r#temp: f32,
    pub r#rh: f32,
    pub r#epoch: i64,
}
impl ::core::default::Default for SensorData {
    fn default() -> Self {
        Self {
            r#device: ::core::default::Default::default(),
            r#temp: ::core::default::Default::default(),
            r#rh: ::core::default::Default::default(),
            r#epoch: ::core::default::Default::default(),
        }
    }
}
impl SensorData {}
impl ::micropb::MessageDecode for SensorData {
    fn decode<IMPL_MICROPB_READ: ::micropb::PbRead>(
        &mut self,
        decoder: &mut ::micropb::PbDecoder<IMPL_MICROPB_READ>,
        len: usize,
    ) -> Result<(), ::micropb::DecodeError<IMPL_MICROPB_READ::Error>> {
        use ::micropb::{PbVec, PbMap, PbString, FieldDecode};
        let before = decoder.bytes_read();
        while decoder.bytes_read() - before < len {
            let tag = decoder.decode_tag()?;
            match tag.field_num() {
                0 => return Err(::micropb::DecodeError::ZeroField),
                1u32 => {
                    let mut_ref = &mut self.r#device;
                    {
                        decoder.decode_string(mut_ref, ::micropb::Presence::Implicit)?;
                    };
                }
                2u32 => {
                    let mut_ref = &mut self.r#temp;
                    {
                        let val = decoder.decode_float()?;
                        let val_ref = &val;
                        if *val_ref != 0.0 {
                            *mut_ref = val as _;
                        }
                    };
                }
                3u32 => {
                    let mut_ref = &mut self.r#rh;
                    {
                        let val = decoder.decode_float()?;
                        let val_ref = &val;
                        if *val_ref != 0.0 {
                            *mut_ref = val as _;
                        }
                    };
                }
                4u32 => {
                    let mut_ref = &mut self.r#epoch;
                    {
                        let val = decoder.decode_int64()?;
                        let val_ref = &val;
                        if *val_ref != 0 {
                            *mut_ref = val as _;
                        }
                    };
                }
                _ => {
                    decoder.skip_wire_value(tag.wire_type())?;
                }
            }
        }
        Ok(())
    }
}
impl ::micropb::MessageEncode for SensorData {
    fn encode<IMPL_MICROPB_WRITE: ::micropb::PbWrite>(
        &self,
        encoder: &mut ::micropb::PbEncoder<IMPL_MICROPB_WRITE>,
    ) -> Result<(), IMPL_MICROPB_WRITE::Error> {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        {
            let val_ref = &self.r#device;
            if !val_ref.is_empty() {
                encoder.encode_varint32(10u32)?;
                encoder.encode_string(val_ref)?;
            }
        }
        {
            let val_ref = &self.r#temp;
            if *val_ref != 0.0 {
                encoder.encode_varint32(21u32)?;
                encoder.encode_float(*val_ref)?;
            }
        }
        {
            let val_ref = &self.r#rh;
            if *val_ref != 0.0 {
                encoder.encode_varint32(29u32)?;
                encoder.encode_float(*val_ref)?;
            }
        }
        {
            let val_ref = &self.r#epoch;
            if *val_ref != 0 {
                encoder.encode_varint32(32u32)?;
                encoder.encode_int64(*val_ref as _)?;
            }
        }
        Ok(())
    }
    fn compute_size(&self) -> usize {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        let mut size = 0;
        {
            let val_ref = &self.r#device;
            if !val_ref.is_empty() {
                size += 1usize + ::micropb::size::sizeof_len_record(val_ref.len());
            }
        }
        {
            let val_ref = &self.r#temp;
            if *val_ref != 0.0 {
                size += 1usize + 4;
            }
        }
        {
            let val_ref = &self.r#rh;
            if *val_ref != 0.0 {
                size += 1usize + 4;
            }
        }
        {
            let val_ref = &self.r#epoch;
            if *val_ref != 0 {
                size += 1usize + ::micropb::size::sizeof_int64(*val_ref as _);
            }
        }
        size
    }
}
