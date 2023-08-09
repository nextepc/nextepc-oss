# Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>

# This file is part of Open5GS.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

systemd_conf_in = '''
    nextepc-mmed.service
    nextepc-sgwcd.service
    nextepc-smfd.service
    nextepc-amfd.service
    nextepc-sgwud.service
    nextepc-upfd.service
    nextepc-hssd.service
    nextepc-pcrfd.service
    nextepc-nrfd.service
    nextepc-scpd.service
    nextepc-ausfd.service
    nextepc-udmd.service
    nextepc-pcfd.service
    nextepc-nssfd.service
    nextepc-bsfd.service
    nextepc-udrd.service
'''.split()

foreach file : systemd_conf_in
    configure_file(
            input : file + '.in',
            output : file,
            configuration : conf_data)
endforeach

systemd_conf = '''
    99-nextepc.netdev
    99-nextepc.network        
'''.split()

foreach file : systemd_conf
    configure_file(
            input : file,
            output : file,
            configuration : conf_data)
endforeach
