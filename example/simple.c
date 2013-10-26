#include <msgpack.h>
#include <stdio.h>

int main(void)
{
	/* msgpack::sbuffer is a simple buffer implementation. */
	msgpack_sbuffer sbuf;
	msgpack_sbuffer_init(&sbuf);

	/* serialize values into the buffer using msgpack_sbuffer_write callback function. */
	msgpack_packer pk;
	msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

	msgpack_pack_array(&pk, 4);
	msgpack_pack_int(&pk, 1);
	msgpack_pack_true(&pk);
	msgpack_pack_raw(&pk, 9);
	msgpack_pack_raw_body(&pk, "123456789", 9);
  
  uint8_t uuid[16] = {0x55,0x0e,0x84,0x00,0xe2,0x9b,0x41,0xd4,0xa7,0x16,0x44,0x66,0x55,0x44,0x00,0x00};
  
  msgpack_pack_uuid(&pk, 16);
  msgpack_pack_uuid_body(&pk, uuid, 16);

	/* deserialize the buffer into msgpack_object instance. */
	/* deserialized object is valid during the msgpack_zone instance alive. */
	msgpack_zone mempool;
	msgpack_zone_init(&mempool, 2048);

	msgpack_object deserialized;
	msgpack_unpack(sbuf.data, sbuf.size, NULL, &mempool, &deserialized);

	/* print the deserialized object. */
	msgpack_object_print(stdout, deserialized);
	puts("");

	msgpack_zone_destroy(&mempool);
	msgpack_sbuffer_destroy(&sbuf);

	return 0;
}

