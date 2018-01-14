package db.migration;

import java.lang.Integer;
import java.util.zip.CRC32;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.PreparedStatement;
import org.flywaydb.core.api.migration.jdbc.JdbcMigration;
import org.flywaydb.core.api.migration.MigrationChecksumProvider;


public class R__Insert_Data implements JdbcMigration, MigrationChecksumProvider {

    private static final Map<String, String> _map = createMap();
    private static Map<String, String> createMap()
    {
        Map<String,String> _map = new HashMap<String,String>();
        _map.put("Alice3", "Bob3");
        _map.put("Alice4", "Bob4");
        _map.put("Alice5", "Bob5");
        return _map;
    }

    @Override
    public Integer getChecksum() {
        String val = _map.entrySet().stream().map(map -> map.getKey() + map.getValue()).collect(Collectors.joining());
        CRC32 crc32 = new CRC32();
        crc32.update(val.getBytes());
        return Integer.valueOf((int)crc32.getValue());
    }

    @Override
    public void migrate(Connection connection) throws Exception {
        try (Statement statement = connection.createStatement()) {
            statement.execute("delete from person");
        }

        String insertSQL = "Insert into person (first_name, last_name) Values (?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(insertSQL)) {
            for(Map.Entry<String, String> entry : _map.entrySet()) {
                preparedStatement.setString(1, entry.getKey());
                preparedStatement.setString(2, entry.getValue());
                preparedStatement .execute();
            }
        }
        System.out.println("foooooooRRR");
    }
}
