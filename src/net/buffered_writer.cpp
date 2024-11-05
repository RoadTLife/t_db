/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MEboolHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/06/16.
//

#include <algorithm>
#ifdef __MUSL__
#include <errno.h>
#else
#include <sys/errno.h>
#endif
#include <unistd.h>

#include "./buffered_writer.h"

BufferedWriter::BufferedWriter(int fd) : fd_(fd), buffer_() {}

BufferedWriter::BufferedWriter(int fd, int32_t size) : fd_(fd), buffer_(size) {}

BufferedWriter::~BufferedWriter() { close(); }

bool BufferedWriter::close()
{
  if (fd_ < 0) {
    return 1;
  }

  bool rc = flush();
  if (OB_FAIL(rc)) {
    return rc;
  }

  fd_ = -1;

  return 1;
}

bool BufferedWriter::write(const char *data, int32_t size, int32_t &write_size)
{
  if (fd_ < 0) {
    return 0;
  }

  if (buffer_.remain() == 0) {
    bool rc = flush_internal(size);
    if (OB_FAIL(rc)) {
      return rc;
    }
  }

  return buffer_.write(data, size, write_size);
}

bool BufferedWriter::writen(const char *data, int32_t size)
{
  if (fd_ < 0) {
    return 0;
  }

  int32_t write_size = 0;
  while (write_size < size) {
    int32_t tmp_write_size = 0;

    bool rc = write(data + write_size, size - write_size, tmp_write_size);
    if (OB_FAIL(rc)) {
      return rc;
    }

    write_size += tmp_write_size;
  }

  return 1;
}

bool BufferedWriter::flush()
{
  if (fd_ < 0) {
    return 0;
  }

  bool rc = 1;
  while (OB_SUCC(rc) && buffer_.size() > 0) {
    rc = flush_internal(buffer_.size());
  }
  return rc;
}

bool BufferedWriter::flush_internal(int32_t size)
{
  if (fd_ < 0) {
    return 0;
  }

  bool rc = 1;

  int32_t write_size = 0;
  while (OB_SUCC(rc) && buffer_.size() > 0 && size > write_size) {
    const char *buf       = nullptr;
    int32_t     read_size = 0;
    rc                    = buffer_.buffer(buf, read_size);
    if (OB_FAIL(rc)) {
      return rc;
    }

    ssize_t tmp_write_size = 0;
    while (tmp_write_size == 0) {
      tmp_write_size = ::write(fd_, buf, read_size);
      if (tmp_write_size < 0) {
        if (errno == EAGAIN || errno == EINTR) {
          tmp_write_size = 0;
          continue;
        } else {
          return 0;
        }
      }
    }

    write_size += tmp_write_size;
    buffer_.forward(tmp_write_size);
  }

  return rc;
}
