package db.migration;

import java.sql.Connection;

import org.flywaydb.core.api.MigrationInfo;
import org.flywaydb.core.api.callback.BaseFlywayCallback;

public class ExampleFlywayCallback extends BaseFlywayCallback {

    private String _descr;

    @Override
    public void beforeEachMigrate(Connection connection, MigrationInfo info) {
        if (info.getChecksum() != null) {
            System.out.println("> beforeEachMigrate " + info.getChecksum().toString() + ", " + info.getDescription());
            _descr = info.getDescription();
        }
    }

    @Override
    public void afterEachMigrate(Connection connection, MigrationInfo info) {
        if (info.getChecksum() != null) {
            System.out.println("> afterEachMigrate " + info.getChecksum().toString() + ", " + info.getDescription());
        }
    }

    @Override
    public void beforeMigrate(Connection connection) {
        System.out.println("> beforeMigrate");
    }

    @Override
    public void afterMigrate(Connection connection) {
        System.out.println("> afterMigrate " + _descr);
    }
}
