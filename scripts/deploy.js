const hre = require("hardhat");

async function main() {
  await hre.run("compile"); // Optional: ensures latest build

  const DigiZone = await hre.ethers.deployContract("DigiZone");
  await DigiZone.waitForDeployment();

  console.log(`✅ DigiZone deployed at: ${DigiZone.target}`);
}

main().catch((error) => {
  console.error("❌ Deployment failed:", error);
  process.exitCode = 1;
});