const grpc = require('@grpc/grpc-js')
const emailModule = require('./email')
const const_module = require('./const')
const message_proto = require('./proto')
const { v4: uuidv4} = require('uuid')

async function GetVarifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try {
        uniqueId = uuidv4();
        console.log("uniqueId is ", uniqueId)
        let text_str = '验证码为' + uniqueId + '有效期三分钟'
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
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode})
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), ()=> {
        server.start()
        console.log('grpc server started')
    })
}

main()