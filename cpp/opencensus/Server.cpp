#include "opencensus/exporters/trace/stdout/stdout_exporter.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/span.h"

#include <Poco/Exception.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <iostream>
#include <string>

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;
using span = opencensus::trace::Span;

// Register stdout exporters.
//opencensus::exporters::trace::StdoutExporter::Register();

static opencensus::trace::AlwaysSampler sampler;

class RequestHandler : public HTTPRequestHandler {
public:
  virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp) {
    auto span = span::StartSpan("RequestHandler", nullptr, {&sampler});
    span.AddAttribute("uri", req.getURI());
    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/plain");
    resp.send() << "Hello Wolrd\n";
    span.AddAnnotation("Hello Wolrd");
    resp.send().flush();
    span.End();
  }
};

class RequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
  virtual HTTPRequestHandler *
  createRequestHandler(const HTTPServerRequest &req) {
    return new RequestHandler();
  }
};

class ServerApp : public ServerApplication {
protected:
  int main(const vector<string> &) {
    int port = 8080;
    HTTPServerParams *pParams = new HTTPServerParams;
    pParams->setKeepAlive(false);
    pParams->setMaxThreads(4);
    HTTPServer s(new RequestHandlerFactory, ServerSocket(port), pParams);
    s.start();
    cout << endl << "Server started on port " << port << endl;
    waitForTerminationRequest(); // wait for CTRL-C or kill
    s.stop();
    return Application::EXIT_OK;
  }
};

int main(int argc, char **argv) {
  ServerApp app;
  return app.run(argc, argv);
}
