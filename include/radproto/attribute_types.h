#pragma once

namespace RadProto
{
    enum Attribute_Types
    {
        USER_NAME = 1,
        USER_PASSWORD = 2,
        CHAP_PASSWORD = 3,
        NAS_IP_ADDRESS = 4,
        NAS_PORT = 5,
        SERVICE_TYPE = 6,
        FRAMED_PROTOCOL = 7,
        FRAMED_IP_ADDRESS = 8,
        FRAMED_IP_NETMASK = 9,
        FRAMED_ROUTING = 10,
        FILTER_ID = 11,
        FRAMED_MTU = 12,
        FRAMED_COMPRESSION = 13,
        LOGIN_IP_HOST = 14,
        LOGIN_SERVICE = 15,
        LOGIN_TCP_PORT = 16,
        REPLY_MESSAGE = 18,
        CALLBACK_NUMBER = 19,
        CALLBACK_ID = 20,
        FRAMED_ROUTE = 22,
        FRAMED_IPX_NETWORK = 23,
        STATE = 24,
        CLASS = 25,
        VENDOR_SPECIFIC = 26,
        SESSION_TIMEOUT = 27,
        IDLE_TIMEOUT = 28,
        TERMINATION_ACTION = 29,
        CALLED_STATION_ID = 30,
        CALLING_STATION_ID = 31,
        NAS_IDENTIFIER = 32,
        PROXY_STATE = 33,
        LOGIN_LAT_SERVICE = 34,
        LOGIN_LAT_NODE = 35,
        LOGIN_LAT_GROUP = 36,
        FRAMED_APPLETALK_LINK = 37,
        FRAMED_APPLETALK_NETWORK = 38,
        FRAMED_APPLETALK_ZONE = 39,
        CHAP_CHALLENGE = 60,
        NAS_PORT_TYPE = 61,
        PORT_LIMIT = 62,
        LOGIN_LAT_PORT = 63,
        EAP_MESSAGE = 79,
        MESSAGE_AUTHENTICATOR = 80
    };
}