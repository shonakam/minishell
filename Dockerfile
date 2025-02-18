# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 20:50:21 by shonakam          #+#    #+#              #
#    Updated: 2025/02/18 20:50:22 by shonakam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.18

ENV LANG=C.UTF-8 \
    TERM=xterm-256color

RUN apk update && apk add --no-cache \
    bash \
    readline \
    readline-dev \
    valgrind \
    build-base \
    gcc \
    g++ \
    make \
    cmake \
    git \
    vim \
    gdb \
    && rm -rf /var/cache/apk/*

WORKDIR /app

CMD ["sh"]
