const nodemailer = require('nodemailer');
const config_module = require('./config')

/** 
 * 创建发送邮件的代理 // "CTg3VgbG6J3yessd"
*/
let transport = nodemailer.createTransport({
    host: 'smtp.163.com',
    port: 465,
    secure: true,
    auth: {
        user: config_module.email_user,
        pass: config_module.email_pass
    }
});

function SendMail(mailOptions_) {
    return new Promise(function(resolve, reject){
        transport.sendMail(mailOptions_, function(error, info) {
            if (error) {
                console.log(error);
                reject(error);
            } else {
                console.log('邮件已成功发送:' + info.response);
                resolve(info.response);
            }
        });
    })
}

module.exports.SendMail = SendMail;