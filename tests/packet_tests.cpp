#define BOOST_TEST_MODULE RadProtoPacketTests

#include "radproto/packet.h"
#include "radproto/attribute.h"
#include "radproto/vendor_attribute.h"
#include "attribute_types.h"
#include "attribute.h"
#include "error.h"
#include <memory>
#include <array>
#include <vector>
#include <set>
#include <string>
#include <cstdint> //uint8_t, uint32_t

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wparentheses"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop

namespace
{
    RadProto::Attribute* findAttribute(const std::vector<RadProto::Attribute*>& attributes, RadProto::Attribute_Types type)
    {
        for (const auto& b : attributes)
        {
            if (b->type() == type)
                return b;
        }
        return nullptr;
    }
}

BOOST_AUTO_TEST_SUITE(PacketTests)

BOOST_AUTO_TEST_CASE(PacketBufferConstructor)
{
       std::array<uint8_t, 4096> d {0x01, 0x7c, 0x00, 0x5c, 0x5d, 0xc1, 0x95, 0x4e, 0x15, 0xc8, 0xfd, 0x76, 0x41, 0x77, 0xbb, 0xfc, 0x6e, 0x5f, 0xda, 0x8a, 0x01, 0x06, 0x74, 0x65, 0x73, 0x74, 0x02, 0x12, 0xc1, 0x07, 0xf2, 0xcc, 0x60, 0x4f, 0x36, 0x03, 0x26, 0xe2, 0x05, 0x3d, 0x79, 0x5b, 0xe5, 0xd6, 0x04, 0x06, 0x7f, 0x00, 0x00, 0x01, 0x05, 0x06, 0x00, 0x00, 0x00, 0x01, 0x50, 0x12, 0xc3, 0xbe, 0x0e, 0x1a, 0xab, 0xcf, 0x2e, 0x7c, 0x7c, 0x00, 0x8c, 0x85, 0x9b, 0x32, 0x65, 0x3b, 0x07, 0x06, 0x00, 0x00, 0x00, 0x01, 0x1a, 0x0c, 0x00, 0x00, 0x00, 0xab, 0x01, 0x06, 0x00, 0x00, 0x00, 0x03};

    RadProto::Packet p(d, 92, "secret");

    BOOST_CHECK_EQUAL(p.type(), 1);

    BOOST_CHECK_EQUAL(p.id(), 0x7c);

    std::array<uint8_t, 16> authValues = p.auth();
    std::array<uint8_t, 16> authExpected {0x5d, 0xc1, 0x95, 0x4e, 0x15, 0xc8, 0xfd, 0x76, 0x41, 0x77, 0xbb, 0xfc, 0x6e, 0x5f, 0xda, 0x8a};

    BOOST_TEST(authValues == authExpected, boost::test_tools::per_element());

    const auto& attrs = p.attributes();
    auto* attr0 = findAttribute(attrs, RadProto::USER_NAME);

    BOOST_REQUIRE(attr0 != nullptr);
    BOOST_CHECK_EQUAL(attr0->type(), RadProto::USER_NAME);
    BOOST_CHECK_EQUAL(attr0->toString(), "test");

    auto* attr1 = findAttribute(attrs, RadProto::USER_PASSWORD);

    BOOST_REQUIRE(attr1 != nullptr);
    BOOST_CHECK_EQUAL(attr1->type(), RadProto::USER_PASSWORD);
    BOOST_CHECK_EQUAL(attr1->toString(), "123456");

    auto* attr2 = findAttribute(attrs, RadProto::NAS_IP_ADDRESS);

    BOOST_REQUIRE(attr2 != nullptr);
    BOOST_CHECK_EQUAL(attr2->type(), RadProto::NAS_IP_ADDRESS);
    BOOST_CHECK_EQUAL(attr2->toString(), "127.0.0.1");

    auto* attr3 = findAttribute(attrs, RadProto::NAS_PORT);

    BOOST_REQUIRE(attr3 != nullptr);
    BOOST_CHECK_EQUAL(attr3->type(), RadProto::NAS_PORT);
    BOOST_CHECK_EQUAL(attr3->toString(), "1");

    auto* attr4 = findAttribute(attrs, RadProto::MESSAGE_AUTHENTICATOR);

    BOOST_REQUIRE(attr4 != nullptr);
    BOOST_CHECK_EQUAL(attr4->type(), RadProto::MESSAGE_AUTHENTICATOR);
    BOOST_CHECK_EQUAL(attr4->toString(), "C3BE0E1AABCF2E7C7C008C859B32653B");

    auto* attr5 = findAttribute(attrs, RadProto::FRAMED_PROTOCOL);

    BOOST_REQUIRE(attr5 != nullptr);
    BOOST_CHECK_EQUAL(attr5->type(), RadProto::FRAMED_PROTOCOL);
    BOOST_CHECK_EQUAL(attr5->toString(), "1");

    std::vector<RadProto::VendorSpecific> vendor = p.vendorSpecific();

    BOOST_CHECK_EQUAL(vendor[0].vendorId(), 171);
    BOOST_CHECK_EQUAL(vendor[0].vendorType(), 1);
    BOOST_CHECK_EQUAL(vendor[0].toString(), "00000003");

    std::set<uint8_t> types {RadProto::USER_NAME, RadProto::USER_PASSWORD, RadProto::NAS_IP_ADDRESS, RadProto::NAS_PORT, RadProto::MESSAGE_AUTHENTICATOR, RadProto::FRAMED_PROTOCOL, RadProto::VENDOR_SPECIFIC};

    BOOST_REQUIRE_EQUAL(attrs.size(), 6);
    BOOST_CHECK(types.count(attrs[0]->type()) == 1);
    BOOST_CHECK(types.count(attrs[1]->type()) == 1);
    BOOST_CHECK(types.count(attrs[2]->type()) == 1);
    BOOST_CHECK(types.count(attrs[3]->type()) == 1);
    BOOST_CHECK(types.count(attrs[4]->type()) == 1);
    BOOST_CHECK(types.count(attrs[5]->type()) == 1);

    BOOST_REQUIRE_EQUAL(vendor.size(), 1);
    BOOST_CHECK(types.count(vendor[0].vendorType()) == 1);
}

BOOST_AUTO_TEST_SUITE_END()