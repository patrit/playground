FROM alpine:3.11.3 as build
RUN apk --no-cache add openjdk11-jdk maven

# fetch maven dependencies
WORKDIR /build
COPY pom.xml pom.xml
RUN mvn dependency:go-offline
# build
COPY src src
RUN mvn clean package

# build JDK with less modules
RUN apk --no-cache add openjdk11
RUN JAVA_DEPS=$(/usr/lib/jvm/java-11-openjdk/bin/jdeps --list-deps target/*.jar | xargs | tr ' ' ',') && \
    echo $JAVA_DEPS && \
    /usr/lib/jvm/default-jvm/bin/jlink \
    --no-header-files --no-man-pages --compress=2 --strip-debug \
    --module-path /usr/lib/jvm/java-11-openjdk/jmods/ \
    --add-modules $JAVA_DEPS,jdk.unsupported,java.naming,java.desktop,java.management,java.security.jgss,java.instrument \
    --output /jdk-minimal


# prepare a fresh Alpine Linux with JDK
FROM alpine:3.11.3
# get result from build stage
COPY --from=build /build/target/*.jar /app.jar
COPY --from=build /jdk-minimal /opt/jdk/
VOLUME /tmp
EXPOSE 8080
CMD /opt/jdk/bin/java $JAVA_OPTS -Djava.security.egd=file:/dev/./urandom -jar /app.jar

