package ch.demo;

import io.quarkus.redis.client.RedisClient;

import java.util.List;
import java.util.stream.Collectors;

import javax.inject.Inject;
import javax.inject.Singleton;

@Singleton
class KVService {

	@Inject
	RedisClient redisClient;

	String getString(String key) {
		return redisClient.get(key).toString();
	}

	List<String> getStringList(String key) {
		return redisClient.lrange(key, "0", "-1").stream().map(r -> r.toString()).collect(Collectors.toList());
	}

}