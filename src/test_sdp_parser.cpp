#include <stdio.h>
#include <fstream>
#include <sdp/SDP.h>
#include <sdp/Reader.h>
#include <sdp/Writer.h>

int main() {

  
  printf("\n\ntest_sdp_parser\n\n");

  /* read SDP file. */
  std::ifstream ifs("example.sdp", std::ios::in);
  if(!ifs.is_open()) {
    return false;
  }

  std::string str( (std::istreambuf_iterator<char>(ifs)) , std::istreambuf_iterator<char>());

  /* parse the source into a sdp::SDP */
  sdp::SDP session;
  sdp::Reader reader;
  sdp::Writer writer;
  sdp::Media* video = NULL;
  sdp::Attribute* ice_ufrag = NULL;
  sdp::Attribute* ice_pwd = NULL;

  reader.parse(str, &session);

  /* retrieve the first video Media element */
  if (session.find(sdp::SDP_VIDEO, &video)) {

    printf("Found video!\n");

    if (video->find(sdp::SDP_ATTR_ICE_UFRAG, &ice_ufrag)) {
      printf("ICE-UFRAG: %s\n", ice_ufrag->value.c_str());
    }

    if (video->find(sdp::SDP_ATTR_ICE_PWD, &ice_pwd)) {
      printf("ICE-PWD: %s\n", ice_pwd->value.c_str());
    }
  }

  std::string created_sdp = writer.toString(&session);
  printf("---\n");
  printf("%s\n", created_sdp.c_str());

  return 0;
}
