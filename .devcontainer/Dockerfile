# Используем базовый образ с GCC и CMake
FROM gcc:14.2.0

RUN apt update && \
    apt install -y \
    git \
    cmake \
    make \
    g++ \
    libgtest-dev \
    libgmock-dev

# Устанавливаем необходимые зависимости
RUN apt-get update && apt-get install -y \
    cmake python3 python3-dev python3-pip wrk clangd\
    && rm -rf /var/lib/apt/lists/*

RUN pip install numpy --break-system-packages
# Устанавливаем рабочую директорию
WORKDIR /workspace
