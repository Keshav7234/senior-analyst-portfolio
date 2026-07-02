FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    pkg-config \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Install vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git /vcpkg && \
    cd /vcpkg && ./bootstrap-vcpkg.sh

ENV PATH="/vcpkg:$PATH"

# Install C++ dependencies
RUN vcpkg install crow nlohmann-json sqlite3

# Create app directory
WORKDIR /app

# Copy C++ source
COPY cpp-backend/ .

# Build application
RUN mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    cmake --build . --config Release

# Expose port
EXPOSE 8080

# Run application
CMD ["./build/portfolio_server"]
