Default route (catch-all):
0.0.0.0/0 => 192.168.1.1
====================================
Basic Diagram Structure
Left and Right IP Addresses:

Left side: Usually represents clients/hosts (like Client A, Client B)
Right side: Usually represents router interfaces or other network devices
Each device needs an IP address and subnet mask to communicate

Key Components in Diagrams:

Clients/Hosts - End devices that need to communicate
Switches - Connect devices in the same network (no IP needed)
Routers - Connect different networks (each interface needs IP)
Internet - External network connection

What the Masks Mean:
The subnet mask determines which devices can communicate directly:

Same network: Devices with same network portion (determined by mask)
Different networks: Need router to communicate

How to Solve Each Level:
Basic Rules:

Same network devices must have:

Same subnet mask
IP addresses in the same network range
No reserved IPs (network address, broadcast address)
------------------------------------------------

Router interfaces must:

Not have overlapping IP ranges
Each interface connects to a different network
------------------------------------------------

Routing tables must specify:

Destination: Where packets should go (IP/CIDR or default 0.0.0.0/0)
Next hop: IP of the next router interface to reach destination
------------------------------------------------

Example Problem-Solving Process:
Level 1 Example:

Client A and Client B need to communicate
Both have /24 mask (255.255.255.0)
If Client B is 104.94.23.12/24
Client A must be in range 104.94.23.1 to 104.94.23.254
Network: 104.94.23.0/24
------------------------------------------------
Level 4 Example (Router):

Router has 3 interfaces (R1, R2, R3)
Each interface connects to different network
IP ranges cannot overlap between interfaces
If R2: 63.12.111.0/25 and R3: 63.12.111.192/26
R1 must use different range, like 63.12.111.128/28

Common Tasks You'll Need to Do:

Calculate valid IP ranges using subnet masks
Avoid IP conflicts between router interfaces
Set up routing tables for inter-network communication
Use reserved IP ranges appropriately (10.x.x.x, 192.168.x.x, 172.16-31.x.x)

Tools to Help:
bash# Use ipcalc to verify your subnets
ipcalc 192.168.1.0/24
----------------------------------------------

# Check if two IPs are in same network
ipcalc 192.168.1.10/24 192.168.1.50/24
The key is understanding that devices must be in the same network (same network address portion) to communicate directly, otherwise they need routing through routers. GitHub - caroldaniel/42sp-cursus-netpractice: A guide to networking concepts.RetryClaude does not have the ability to run the code it generates yet.YMi have: host g: ion routes: 8.8.8./16: whats that? => 99.`98.200.1 whats that?EditYou have a routing table entry that looks like this:
Destination: 8.8.8.8/16
Next Hop: 99.98.200.1
Let me break this down:
Destination: 8.8.8.8/16

8.8.8.8 = Google's public DNS server (a real internet address)
/16 = Subnet mask that covers the range 8.8.0.0 to 8.8.255.255
This means: "Any packet going to any IP in the 8.8.x.x network"

Next Hop: 99.98.200.1

This is the gateway/router IP that your host will send packets to
When your host wants to reach anything in the 8.8.x.x range, it forwards the packet to 99.98.200.1
99.98.200.1 is likely a router interface that knows how to reach the internet

What This Route Does:
Host G wants to ping 8.8.8.8
      ↓
Host G checks routing table
      ↓ 
"8.8.8.8 matches 8.8.8.8/16 rule"
      ↓
Host G sends packet to 99.98.200.1 (next hop)
      ↓
Router at 99.98.200.1 forwards packet toward internet
In NetPractice Context:

Your host G needs to be in the same network as 99.98.200.1 to reach it
So Host G's IP must be something like 99.98.200.x/24 (depending on the subnet mask)
The router interface at 99.98.200.1 then handles getting packets to the 8.8.8.8 destination
===============================================
The "reserved IP ranges" are specific IP address blocks that are designated for private networks only - they cannot be used on the public internet.
The Three Private IP Ranges:
1. Class A: 10.0.0.0 to 10.255.255.255

CIDR: 10.0.0.0/8
Subnet Mask: 255.0.0.0
Total IPs: ~16.7 million addresses
Use: Large corporate networks, data centers

2. Class B: 172.16.0.0 to 172.31.255.255

CIDR: 172.16.0.0/12
Subnet Mask: 255.240.0.0
Total IPs: ~1 million addresses
Use: Medium-sized networks

3. Class C: 192.168.0.0 to 192.168.255.255

CIDR: 192.168.0.0/16
Subnet Mask: 255.255.0.0
Total IPs: ~65,000 addresses
Use: Home networks, small offices

Why These Are "Reserved":
Private Networks Only:

These IPs are never routed on the public internet
Internet routers will drop packets with these addresses
Multiple organizations can use the same private IPs without conflict

Example:
Your home: 192.168.1.100
My home:   192.168.1.100  ← Same IP, no problem!
Both work because they're in separate private networks.
===================================================
CORRECT Usage:
Host A: 192.168.1.10/24
Host B: 10.0.0.50/24  
Router: 172.16.1.1/24
❌ WRONG Usage:
Host A: 8.8.8.8/24      ← Google's public DNS
Host B: 1.1.1.1/24      ← Cloudflare's public DNS  
Router: 151.101.1.1/24  ← Reddit's public IP

Other Reserved Ranges to Avoid:
c// Don't use these in NetPractice:
127.0.0.0/8     // Loopback (127.0.0.1 = localhost)
224.0.0.0/4     // Multicast  
240.0.0.0/4     // Experimental
0.0.0.0/8       // "This network"

Practical Rule for NetPractice:
Always start your IPs with:

10.x.x.x (most flexible, huge range)
192.168.x.x (common for small networks)
172.16.x.x to 172.31.x.x (medium networks)

Example Network Design:
Network 1: 10.0.1.0/24    (10.0.1.1 - 10.0.1.254)
Network 2: 10.0.2.0/24    (10.0.2.1 - 10.0.2.254)  
Network 3: 10.0.3.0/24    (10.0.3.1 - 10.0.3.254)
=====================================================