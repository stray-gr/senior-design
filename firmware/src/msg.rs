#[derive(Debug, PartialEq, Clone)]
pub struct Cat {
    pub r#name: ::micropb::heapless::String<36>,
    pub r#age: i32,
}
impl ::core::default::Default for Cat {
    fn default() -> Self {
        Self {
            r#name: ::core::default::Default::default(),
            r#age: ::core::default::Default::default(),
        }
    }
}
impl Cat {}
impl ::micropb::MessageDecode for Cat {
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
                    let mut_ref = &mut self.r#name;
                    {
                        decoder.decode_string(mut_ref, ::micropb::Presence::Implicit)?;
                    };
                }
                2u32 => {
                    let mut_ref = &mut self.r#age;
                    {
                        let val = decoder.decode_int32()?;
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
impl ::micropb::MessageEncode for Cat {
    fn encode<IMPL_MICROPB_WRITE: ::micropb::PbWrite>(
        &self,
        encoder: &mut ::micropb::PbEncoder<IMPL_MICROPB_WRITE>,
    ) -> Result<(), IMPL_MICROPB_WRITE::Error> {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        {
            let val_ref = &self.r#name;
            if !val_ref.is_empty() {
                encoder.encode_varint32(10u32)?;
                encoder.encode_string(val_ref)?;
            }
        }
        {
            let val_ref = &self.r#age;
            if *val_ref != 0 {
                encoder.encode_varint32(16u32)?;
                encoder.encode_int32(*val_ref as _)?;
            }
        }
        Ok(())
    }
    fn compute_size(&self) -> usize {
        use ::micropb::{PbVec, PbMap, PbString, FieldEncode};
        let mut size = 0;
        {
            let val_ref = &self.r#name;
            if !val_ref.is_empty() {
                size += 1usize + ::micropb::size::sizeof_len_record(val_ref.len());
            }
        }
        {
            let val_ref = &self.r#age;
            if *val_ref != 0 {
                size += 1usize + ::micropb::size::sizeof_int32(*val_ref as _);
            }
        }
        size
    }
}
