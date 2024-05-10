#include "CircularArray.h"

#define DEBUG_ARRAY(...)  {char _b[100]; sprintf(_b, __VA_ARGS__); Serial.println(_b);}
#define DEB_ARRAY(...)  {char _b[100]; sprintf(_b, __VA_ARGS__); Serial.print(_b);}

//define DEBUG_ARRAY(...) {}
//define DEB_ARRAY(...) {}

CircularArray::CircularArray() {
    start = 0;
    end = 0;
    size = sizeof(buf);
  }

int CircularArray::length() {
    return end >= start ? end - start : end - start + size;
  }

  uint8_t& CircularArray::operator [](int index) {
    int ind;

    if (index > length ()) {
      DEBUG_ARRAY("Index out of range: %d", index);
    }

    ind = (index + start) % size;
    return buf[ind];
  }

  int CircularArray::expand (int len) {
    int le;
    le = len;
    if (length() + le > size) {
      le = size - length();
      DEBUG_ARRAY("Expand past buffer size: requested %d limted to %d", len, le);
    }

    end += le;
    if (end > size) end -= size; 
    return le;
  }

  int CircularArray::shrink(int len) {
    int le;
    le = len;
    if (le > length()) {
      DEBUG_ARRAY("Shrink past buffer size: requested %d limited to %d", len, length());
      le = length();
    }
    start += le;
    if (start > size) start -= size; 
    return le;
  }

  int CircularArray::copy_in(uint8_t *data, int index, int len) {
    int le; 
    int i;
    le = len;
    if (index + len > length()) {
      le = length() - index;
      DEBUG_ARRAY("Trying to copy_in too much: %d limited to %d", len, le);
    }
    for (i = 0; i < le; i++) {
      buf[(start + index + i) % size] = data[i];
    }
    return le;
  }

  int CircularArray::copy_out(uint8_t *data, int index, int len) {
    int le;
    int i;

    le = len;
    if (index + len > length()) {
      le = length() - index;
      DEBUG_ARRAY("Trying to copy_out too much: %d limited to %d", len, le);
    }
    for (i = 0; i < le; i++) {
      data[i] = buf[(start + index + i) % size];
    }
    return le;
  }


  int CircularArray::append(uint8_t *data, int len) {
    int le;
    int i;

    // check length
    le = len;
    if (length() + le > size) {
      le = size - length();
      DEBUG_ARRAY("Append past buffer size: requested %d limted to %d", len, le);
    }
    // copy
    for (i = 0; i < le; i++) {
      buf[(end + i) % size] = data[i];
    }
    // expand
    end += le;
    if (end > size) end -= size; 
    return le;
  }

  int CircularArray::extract(uint8_t *data, int len) {
    int le;
    int i;

    // check length
    le = len;
    if (len > length()) {
      le = length();
      DEBUG_ARRAY("Trying to extract too much: %d limited to %d", len, le);
    }
    // copy
    for (i = 0; i < le; i++) {
      data[i] = buf[(start + i) % size];
    }
    // shrink
    start += le;
    if (start > size) start -= size; 
    return le;
  }

  void CircularArray::show() {
    int i;
    for (i = 0; i < length(); i++) 
      DEB_ARRAY("%d ", buf[(start + i) % size]);
    DEBUG_ARRAY("");
  }

  void CircularArray::clear() {
    start = 0;
    end = 0;
  }
