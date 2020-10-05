package ch.demo;

import java.util.List;

import javax.inject.Inject;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;


@Path("/")
@Produces(MediaType.APPLICATION_JSON)
//@Consumes(MediaType.APPLICATION_JSON)
public class ExampleResource {

    @Inject
    KVService service;

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    @Path("/lvid/{key}")
    public List<String> get(@PathParam("key") String key) {
        return service.getStringList(key);
    }
}