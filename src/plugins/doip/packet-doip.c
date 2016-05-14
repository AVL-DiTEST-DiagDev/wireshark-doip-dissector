/**
* Copyright 2017 The Open Source Research Group,
*                University of Erlangen-Nürnberg
*
* Licensed under the GNU AFFERO GENERAL PUBLIC LICENSE, Version 3.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     https://www.gnu.org/licenses/gpl.html
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "packet-doip.h"

static const char *DOIP_FULLNAME = "Diagnostic over IP";
static const char *DOIP_SHORTNAME = "DoIP";
static const char *DOIP_ABBREV = "doip";

static const guint32 TCP_DATA_PORT = 13400;
static const guint32 UDP_DISCOVERY_PORT = 13400;
static const guint32 UDP_TEST_EQUIPMENT = 13400;

static int proto_doip = -1;

static void
dissect_doip_tcp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    /* suppress warning for unused variables */
    if(tvb) {
        tvb = NULL;
    }
    if(tree) {
        tree = NULL;
    }

    col_set_str(pinfo->cinfo, COL_PROTOCOL, DOIP_SHORTNAME);
    col_clear(pinfo->cinfo, COL_INFO);
}

static void
dissect_doip_udp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    /* suppress warning for unused variables */
    if(tvb) {
        tvb = NULL;
    }
    if(tree) {
        tree = NULL;
    }

    col_set_str(pinfo->cinfo, COL_PROTOCOL, DOIP_SHORTNAME);
    col_clear(pinfo->cinfo, COL_INFO);

    register_udp_test_equipment_messages(tree);
}

static void
register_udp_test_equipment_messages(proto_tree *tree)
{
    /* TODO by dust */
    /*
    gboolean has_non_default_port_communication;
    proto_item *udp_package;
    */
}


void
proto_register_doip(void)
{
    proto_doip = proto_register_protocol (
        DOIP_FULLNAME,
        DOIP_SHORTNAME,
        DOIP_ABBREV
    );
}

void
proto_reg_handoff_doip(void)
{
    static dissector_handle_t doip_tcp_handle;
    static dissector_handle_t doip_udp_handle;

    doip_tcp_handle = create_dissector_handle(dissect_doip_tcp, proto_doip);
    doip_udp_handle = create_dissector_handle(dissect_doip_udp, proto_doip);

    dissector_add_uint("tcp.port", TCP_DATA_PORT, doip_tcp_handle);
    dissector_add_uint("udp.port", UDP_DISCOVERY_PORT, doip_udp_handle);
}

