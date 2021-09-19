FROM python:3.9-slim AS builder

RUN apt-get update && apt-get install -y --no-install-recommends pipenv curl

WORKDIR /app
ENV LANG en_US.UTF-8
ENV PIPENV_VENV_IN_PROJECT=1

RUN curl -s -L https://github.com/tektoncd/cli/releases/download/v0.20.0/tkn_0.20.0_Linux_x86_64.tar.gz -o tkn.tar.gz && \
    tar xf tkn.tar.gz tkn && \
    rm -f tkn.tar.gz

COPY Pipfile.lock .
RUN pipenv install --ignore-pipfile --deploy

COPY main.py .

EXPOSE 8080
CMD .venv/bin/uvicorn main:app --host=0.0.0.0 --port=8080
