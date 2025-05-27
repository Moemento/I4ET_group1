# 🚢 PlatformManager Smart Contract

**PlatformManager** is a Solidity smart contract designed to manage secure mission logging, role-based access control, and usage quota enforcement for advanced maritime systems. It is ideal for self-stabilizing platforms used on naval or offshore vessels where device operations must be logged, regulated, and limited with trust and transparency.

---

## 📦 Features

### 🔐 Role-Based Access Control
- Supports three roles:
  - `Admin`: full privileges
  - `Operator`: limited to mission logging
  - `None`: default for new accounts
- Roles are securely managed and recorded via on-chain events.

### 🚀 Mission Logging
- Operators can log detailed mission records including:
  - Device type (e.g., `"WaterJet"`, `"MissileLauncher"`)
  - Mission purpose (e.g., `"FireSuppression"`, `"Defense"`)
  - Status of execution (`true` for success, `false` for failure)
- Each log entry is timestamped and permanently stored on-chain.

### 📊 Usage Quota Enforcement
- Operators are restricted to a maximum of **5 missions per 24 hours**.
- Usage resets automatically every new day based on block timestamp.
- Designed to enforce operational discipline and prevent system abuse.

### 📈 Public Data Access
- Easily query:
  - Role of any address
  - Daily usage stats
  - Complete mission history
- Optimized for integration with monitoring tools or front-end dashboards.

---

## 🧰 How to Use (Remix IDE)

### 1. Deploying the Contract
- Open [Remix IDE](https://remix.ethereum.org)
- Create a file named `PlatformManager.sol` and paste the contract code.
- Compile with Solidity version `0.8.18` or higher.
- Deploy using the **Remix VM (Prague)** environment.

### 2. Assigning Roles
- Use `assignRole(address_user, uint8_role)`
  - `1` for Operator, `2` for Admin
- Only the contract deployer (initial admin) can assign roles.

### 3. Logging a Mission
- Switch to an account with Operator role.
- Call `logMission(string deviceType, string missionType, bool success)`
- Example: `"Radar"`, `"Surveillance"`, `true`
- If usage quota is exceeded, the transaction will revert.

### 4. Checking Data
- `getMissions()` – returns all logged missions
- `getMissionCount()` – total mission entries
- `roles(address)` – view assigned role
- `dailyUsage(address)` – how many missions logged today
- `lastUsageDay(address)` – timestamp for usage reset

---

## 💡 Use Cases

- **Maritime defense systems** with restricted deployment privileges  
- **Firefighting platforms** with mission logging and operator accountability  
- **Offshore inspection systems** with role-based access and quotas  
- **Fleet command platforms** with auditable usage records

---

## 🛡️ Security and Best Practices

- Role-restricted access using Solidity modifiers
- Events for all sensitive state changes (`RoleAssigned`, `MissionLogged`)
- State persistence via mappings and structured arrays
- Timestamp-based quota resets for reliability and automation

---

## 📁 Directory Structure

