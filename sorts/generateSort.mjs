#!/usr/bin/env zx

if (process.argv.length === 3) {
    process.exit(1);
}

const sortName = process.argv[3];

fs.appendFileSync('CMakeLists.txt', `add_subdirectory(${sortName})\n`);

await $`mkdir ${sortName}`;
cd(sortName);
fs.writeFileSync('CMakeLists.txt', "add_subdirectory(src)\n" +
    "add_subdirectory(test)\n");

await $`mkdir src`;
await $`mkdir test`;

fs.writeFileSync('./src/CMakeLists.txt', "FILE(GLOB SRC_FILES *.cpp)\n" +
    "\n" +
    `add_library(${sortName} STATIC \${SRC_FILES})\n` +
    "\n");

const testTargetName = sortName + 'Test';
fs.writeFileSync('./test/CMakeLists.txt', "FILE(GLOB TEST_FILES *.test.cpp)\n" +
    "\n" +
    `add_executable(${testTargetName} \${TEST_FILES})\n` +
    "\n" +
    `target_link_libraries(${testTargetName} GTest::gtest_main ${sortName})\n` +
    `target_include_directories(${testTargetName} PUBLIC ../src)\n` +
    "\n" +
    "include(GoogleTest)\n" +
    `gtest_discover_tests(${testTargetName})\n`)

fs.writeFileSync('README.md', `# ${sortName} sort description\n`);

const includeGuard = "DSA_" + sortName.toUpperCase() + "_H"
const functionName = sortName + 'Sort';
fs.writeFileSync(`./src/${sortName}.h`, `#ifndef ${includeGuard}\n` +
    `#define ${includeGuard}\n` +
    "\n" +
    `void ${functionName}(int data[], size_t size);\n` +
    "\n" +
    `#endif //${includeGuard}\n`);

fs.writeFileSync(`./src/${sortName}.cpp`, `#include "${sortName}.h"\n` +
    "\n" +
    `void ${functionName}(int data[], size_t size) {\n` +
    "    return;\n" +
    "}\n");

fs.writeFileSync(`./test/${sortName}.test.cpp`, "#include <gtest/gtest.h>\n" +
    `#include "${sortName}.h"\n` +
    "\n" +
    `TEST(${sortName}, test1) {\n` +
    "    EXPECT_EQ(0, 0);\n" +
    "}");
