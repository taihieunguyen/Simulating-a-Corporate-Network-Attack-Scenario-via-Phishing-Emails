# Simulating-a-Corporate-Network-Attack-Scenario-via-Phishing-Emails
This project simulates a cyber attack on an enterprise network through phishing emails. It demonstrates how a compromised employee machine leads to domain controller infiltration and data extraction. The goal is to raise awareness of social engineering threats and propose effective countermeasures using the MITRE ATT&amp;CK framework.
  
## AI-searching Architecture

![Infrastructure Architecture](https://github.com/taihieunguyen/Simulating-a-Corporate-Network-Attack-Scenario-via-Phishing-Emails/blob/main/diagrams/Application%20Architecture.png?raw=true)

## Key Features
- Step-by-step simulation of a phishing-based APT (Advanced Persistent Threat) attack.
- Full attack chain from initial compromise to domain privilege escalation and data theft.
- End-to-end simulation of a phishing attack in a Windows-based enterprise network.
- Uses real-world tools like PowerShell Empire, Mimikatz, BloodHound, and Wireshark.
- Defensive recommendations mapped to MITRE ATT&CK techniques.

## Repository Structure

- **/diagrams/**: Contains architecture and attack flow diagrams  
  - `Application Architecture.png`  
  - `Infrastructure Architecture.png`  

- **/report/**: Placeholder for documentation or attack reports (currently empty or under development)

- **/script/**: Source code or scripts related to the attack simulation  
  - `attack.cpp`: C++ source file simulating part of the attack logic  
  - `README.md`: Documentation for the script or project instructions


## Prerequisites
- VirtualBox or VMware to run virtual machines.
- Kali Linux, Windows Server, and Windows 10 ISO images.
- Tools such as: PowerShell Empire (C2 Framework), Mimikatz (Credential Dumping), Wireshark (Traffic Capture and Analysis),...

## Contributing
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m "Add feature"`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

---

## Contact
For questions or support, open an issue on the GitHub repository or contact the maintainer at [taihieunguyen004@gmail.com].
