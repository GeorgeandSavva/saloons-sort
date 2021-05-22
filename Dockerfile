FROM alpine:3.13.5

ARG APP_FOLDER=/app

WORKDIR ${APP_FOLDER}

RUN apk add --no-cache build-base=0.5-r2

COPY main.cpp .

RUN g++ main.cpp -o pr &&\
    adduser -D -H user

COPY data.csv data.csv

USER user

CMD ["./pr", "data.csv"]
