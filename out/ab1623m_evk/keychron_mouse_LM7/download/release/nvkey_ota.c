typedef struct {
    const uint16_t id;
    const uint8_t *p_data;
    const uint32_t len;
} nvid_ota_info_t;

const uint8_t NVID_0x6000_VALUE[] = { 
    0x0a, 0x00, /* Power Saving Active Timeout (little endian)  */
    0x0a, 0x00, /* Power Saving Idle1 Timeout (little endian)  */
    0x0a, 0x00, /* Power Saving Idle2 Timeout (little endian)  */
    0x00, 0x00, /* Power Saving Standby Timeout (little endian)  */
    0x3c, 0x00, /* 2.4G Pairing Timeout (little endian)  */
    0x0a, 0x00, /* 2.4G Reconnect Timeout (little endian)  */
    0x3c, 0x00, /* BT Pairing Timeout (little endian)  */
    0x1e, 0x00, /* BT Reconnect Timeout (little endian)  */
}; 
static_assert(sizeof(NVID_0x6000_VALUE)) == sizeof()));  

nvid_ota_info_t ota_nvid_info[] = {
    { 0x6000, NVID_0x6000_VALUE, len(NVID_0x6000_VALUE) },
};
