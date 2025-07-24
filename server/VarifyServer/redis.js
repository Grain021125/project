const config_module = require('./config');
const Redis = require('ioredis');

const RedisClient = new Redis({
  host: config_module.redis_host,
  port: config_module.redis_port,
  password: config_module.redis_passwd
});

/**
 * 监听错误信息
 */
RedisClient.on("error", (err) => {
  console.log("RedisClient error" + err);
  RedisClient.quit();
})

/**
 * 根据key获取值
 * @param {string} key 键名
 * @return
 */
async function getValue(key) {
  try {
    const result = await RedisClient.get(key);
    if (result == null) {
      console.log('result', '<' + result + '>', 'This key cannot be find.');
      return null;
    }

    console.log('result', '<' + result + '>', 'Get key success!');
    return result;

  } catch (error) {
    console.error("Error getting value from Redis:", error);
    throw error;
  }
}

/**
 * 查询redis中是否存在key
 * @param {*} key
 * @returns
 */
async function Exists(key) {
  try {
    const result = await RedisClient.exists(key);
    if (result == 0) {
      console.log('result', '<' + result + '>', 'This key is null.');
      return null;
    }
    console.log('result', '<' + result + '>', 'With this value!.');
    return result;
  } catch (error) {
    console.error("Error exists from Redis:", error);
    return null;
  }
}

/**
 * 设置key和value以及过期时间
 * @param {*} key
 * @param {*} value
 * @param {*} exptime
 * @returns
 */
async function setValue(key, value, exptime) {
  try {
    await RedisClient.set(key, value, 'EX', exptime);
    return true;
  } catch (error) {
    console.log('Error setValue from Redis:', error);
  }
}

/**
 * 退出函数
 */
function Quit(){
    RedisCli.quit();
}

module.exports = {getValue, Exists, setValue, Quit}