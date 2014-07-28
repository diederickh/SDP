#include <sdp/Types.h>

namespace sdp {

  /* ----------------------------------------------------------- */

  /* generic sdp line */
  Node::Node(Type t)
    :type(t)
  {
  }

  void Node::addNode(Node* n) {
    nodes.push_back(n);
  }

  bool Node::find(Type t, std::vector<Node*>& result) {
    for (size_t i = 0; i < nodes.size(); ++i) {
      if (nodes[i]->type == t) {
        result.push_back(nodes[i]);
      }
    }
    return result.size();
  }

  bool Node::find(MediaType t, Media** m) {
    *m = NULL;
    for (size_t i = 0; i < nodes.size(); ++i) {
      if (nodes[i]->type == SDP_MEDIA) {
        *m = static_cast<Media*>(nodes[i]);
        return true;
      }
    }
    return false;
  }

  bool Node::find(AttrType t, Attribute** a) {
    Attribute* attr;
    *a = NULL;
    for (size_t i = 0; i < nodes.size(); ++i) {
      if (nodes[i]->type == SDP_ATTRIBUTE) {
        attr = static_cast<Attribute*>(nodes[i]);
        if (attr->attr_type == t) {
          *a = static_cast<Attribute*>(nodes[i]);
          return true;
        }
      }
    }
    return false;
  }

  bool Node::find(AttrType t, std::vector<Attribute*>& result) {
    Attribute* attr;
    for (size_t i = 0; i < nodes.size(); ++i) {
      if (nodes[i]->type == SDP_ATTRIBUTE) {
        attr = static_cast<Attribute*>(nodes[i]);
        if (attr->attr_type == t) {
          result.push_back(attr);
        }
      }
    }
    return result.size();
  }

  /* ----------------------------------------------------------- */

  /* v=0 */
  Version::Version()
    :version(0)
    ,Node(SDP_VERSION)
  {
  }

  /* o=- 621762799816690644 7 IN IP4 127.0.0.1 */
  Origin::Origin()
    :net_type(SDP_IN)
    ,addr_type(SDP_IP4)
    ,sess_version(1)
    ,Node(SDP_ORIGIN)
  {
  }

  /* s=- */
  SessionName::SessionName()
    :Node(SDP_SESSION_NAME)
  {
  }

  /* i= */
  SessionInformation::SessionInformation()
    :Node(SDP_SESSION_INFORMATION)
  {
  }

  /* u= */
  URI::URI() 
    :Node(SDP_URI)
  {
  }

  /* e= */
  EmailAddress::EmailAddress()
    :Node(SDP_EMAIL_ADDRESS)
  {
  }

  /* p= */
  PhoneNumber::PhoneNumber() 
    :Node(SDP_PHONE_NUMBER)
  {
  }

  /* c= */
  ConnectionData::ConnectionData()
    :net_type(SDP_IN)
    ,addr_type(SDP_IP4)
    ,Node(SDP_CONNECTION_DATA)
  {
  }

  /* t=0 0 */
  Timing::Timing()
    :start_time(0)
    ,stop_time(0)
    ,Node(SDP_TIMING)
  {
  }

  /* m= */
  Media::Media()
    :media(SDP_MEDIATYPE_NONE)
    ,port(0)
    ,proto(SDP_MEDIAPROTO_NONE)
    ,fmt(0)
    ,Node(SDP_MEDIA)
  {
  }

  /* a= */
  Attribute::Attribute()
    :attr_type(SDP_ATTRTYPE_NONE)
    ,Node(SDP_ATTRIBUTE)
  {
  }

  /* a=rtcp: */
  AttributeRTCP::AttributeRTCP()
    :Attribute()
  {
    attr_type = SDP_ATTR_RTCP;
  }


  AttributeCandidate::AttributeCandidate()
    :component_id(0)
    ,priority(0)
    ,port(0)
    ,rel_port(0)
    ,Attribute()
  {
    attr_type = SDP_ATTR_CANDIDATE;
  }

};
