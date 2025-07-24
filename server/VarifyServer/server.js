const grpc = require('@grpc/grpc-js')
const emailModule = require('./email')
const const_module = require('./const')
const message_proto = require('./proto')
const { v4: uuidv4 } = require('uuid')
const redis_module = require('./redis')
const { error } = require('console')

async function GetVarifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try {
        let query_res = await redis_module.getValue(const_module.code_prefix + call.request.email);
        console.log('query_res is ', query_res);
        if (query_res == null) {
        }

        let uniqueId = query_res;
        if (query_res == null) {
            uniqueId = uuidv4();
            if (uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0, 4);
            }
            let bres = await redis_module.setValue(const_module.code_prefix + call.request.email, uniqueId, 180)//设置验证码三分钟过期
            if (!bres) {
                callback(null, {email: call.request.email,
                    error: const_module.Errors.REDIS_ERR
                });
                return;
            }
        }

        console.log("uniqueId is ", uniqueId)
        let text_str = '您的验证码为' + uniqueId + ',请在三分钟内完成注册'
        //发送邮件
        let mailOptions_ = {
            from: 'grain021125@163.com',
            to: call.request.email,
            subject: '验证码',
            text: text_str
        };

        let send_res = await emailModule.SendMail(mailOptions_);
        console.log("send res is ", send_res);

        callback(null, {
            email: call.request.email,
            error: const_module.Errors.SUCCESS
        });

    } catch (error) {
        console.log("catch error is ", error)

        callback(null, {
            email: call.request.email,
            error: const_module.Errors.EXCEPTION
        });
    }
}

function main() {
    var server = new grpc.Server()
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode })
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), () => {
        server.start()
        console.log('grpc server started')
    })
}

main()