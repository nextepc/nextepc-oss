const mongoose = require('mongoose');
const Schema = mongoose.Schema;
require('mongoose-long')(mongoose);

const Profile = new Schema({

  schema_version: {
    $type: Number,
    default: 1  // Current Schema Version
  },

  title: { $type: String, required: true },

  security: {
    k: String,
    op: String,
    opc: String,
    amf: String,
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
        index: Number,
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
          index: Number,
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

module.exports = mongoose.model('Profile', Profile);
