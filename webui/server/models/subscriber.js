const mongoose = require('mongoose');
const Schema = mongoose.Schema;
require('mongoose-long')(mongoose);

const Subscriber = new Schema({

  schema_version: {
    $type: Number,
    default: 1  // Current Schema Version
  },

  imsi: { $type: String, unique: true, required: true },

  security: {
    k: String,
    op: String,
    opc: String,
    amf: String,
    rand: String,
    sqn: Schema.Types.Long
  },

  access_restriction_data: { 
    $type: Number, 
    default: 32 // Handover to Non-3GPP Access Not Allowed
  },
  subscriber_status: { 
    $type: Number,
    default: 0  // Service Granted
  },
  network_access_mode: {
    $type: Number,
    default: 2 // Only Packet
  },

  subscribed_rau_tau_timer: {
    $type: Number,
    default: 12 // minites
  },

  ambr: {
    downlink: { value: Number, unit: Number },
    uplink: { value: Number, unit: Number }
  },

  slice: [{
    sst: { $type: Number, default: 1, required: true },
    sd: String,
    default_indicator: { $type: Boolean, default: true },
    session: [{
      name: { $type: String, required: true },
      type: {
        $type: Number, default: 2 // IPv4, IPv6 and dualstack IPv4v6
      },
      qos: {
        index: Number, // QCI or 5QI
        arp: {
          priority_level: Number,
          pre_emption_capability: {
            $type: Number, default: 1 // Capability Disabled
          },
          pre_emption_vulnerability: {
            $type : Number, default: 1 // Vulnerability Disabled
          }
        }
      },
      ambr: {
        downlink: { value: Number, unit: Number },
        uplink: { value: Number, unit: Number }
      },
      ue: {
        addr: String,
        addr6: String
      },
      pgw: {
        addr: String,
        addr6: String
      },
      pcc_rule: [{
        flow: [{
          direction: Number,
          description: String
        }],
        qos: {
          index: Number, // 5QI or QCI
          arp: {
            priority_level: Number,
            pre_emption_capability: {
              $type: Number, default: 1 // Capability Disabled
            },
            pre_emption_vulnerability: {
              $type : Number, default: 1 // Vulnerability Disabled
            }
          },
          mbr: {
            downlink: { value: Number, unit: Number },
            uplink: { value: Number, unit: Number }
          },
          gbr: {
            downlink: { value: Number, unit: Number },
            uplink: { value: Number, unit: Number }
          },
        },
      }]
    }]
  }]
}, { typeKey: '$type' });

module.exports = mongoose.model('Subscriber', Subscriber);
