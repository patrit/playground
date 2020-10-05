#include <hiredis/hiredis.h>

int main() {
  struct timeval timeout = { 1, 500000 }; // 1.5 seconds
  redisContext *c = redisConnectWithTimeout("127.0.0.1", 6379, timeout);
  if (c == NULL || c->err) {
    if (c) {
        printf("Error: %s\n", c->errstr);
    } else {
        printf("Can't allocate redis context\n");
    }
    return 1;
  }

  for(int i = 0; i<10000; i++) {
    redisReply *reply;
    redisAppendCommand(c,"lrange list%d 0 -1", i);
    redisGetReply(c,(void *)&reply); // reply for GET
    if (reply->type == REDIS_REPLY_ARRAY) {
      for (int j = 0; j < reply->elements; j++) {
        printf("%d: %d) %s\n", i, j, reply->element[j]->str);
      }
    }
    freeReplyObject(reply);
  }
  redisFree(c);
  return 0;
}
