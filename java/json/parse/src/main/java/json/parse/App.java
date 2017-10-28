package json.parse;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.json.JSONArray;
import org.json.JSONObject;

public class App {
	public static void main(String[] args) throws IOException {
		byte[] bc = Files.readAllBytes(Paths.get("src/main/resources/example.json"));
		String content = new String(bc, "ISO-8859-1");
		JSONObject json = new JSONObject(content);
		System.out.println("Name   : " + json.getString("firstName") + " " + json.getString("lastName"));
		System.out.println("Age    : " + json.getInt("age"));
		System.out.println("Alive  : " + json.getBoolean("isAlive"));
		JSONObject addressObject = json.getJSONObject("address");
		System.out.println("Address: ");
		System.out.println("  " + addressObject.getString("streetAddress"));
		System.out.println("  " + addressObject.getString("city"));

		System.out.println("PhoneNumber: ");
		JSONArray array = json.getJSONArray("phoneNumbers");
		for (int i = 0; i < array.length(); i++) {
			JSONObject item = array.getJSONObject(i);
			System.out.println("  " + item.getString("number"));
		}
	}
}
