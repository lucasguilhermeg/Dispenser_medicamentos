const express = require('express')
const mqtt    = require('mqtt')

const app  = express()
app.use(express.json()) // permite receber JSON nas requisições
app.use(express.static('public'))
// ── Conexão com o broker MQTT ─────────────────────────────
const mqttClient = mqtt.connect('mqtt://broker.hivemq.com')

mqttClient.on('connect', () => {
    console.log('Conectado ao broker MQTT!')
})

// ── Rotas da API REST ─────────────────────────────────────

// Rota de teste — confirma que o servidor está rodando
app.get('/', (req, res) => {
    res.json({ status: 'Servidor do dispenser rodando!' })
})

// Envia uma rotina para o ESP32 via MQTT
app.post('/rotina', (req, res) => {
    const rotina = req.body

    mqttClient.publish(
        'dispenser/rotina',
        JSON.stringify(rotina)
    )

    console.log('Rotina enviada ao ESP32:', rotina)
    res.json({ sucesso: true, mensagem: 'Rotina enviada!' })
})

// Envia um comando manual para o ESP32 via MQTT
app.post('/comando', (req, res) => {
    const comando = req.body

    mqttClient.publish(
        'dispenser/comando',
        JSON.stringify(comando)
    )

    console.log('Comando enviado ao ESP32:', comando)
    res.json({ sucesso: true, mensagem: 'Comando enviado!' })
})

// ── Inicia o servidor ─────────────────────────────────────
const PORT = process.env.PORT || 3000
app.listen(PORT, () => {
    console.log(`Servidor rodando na porta ${PORT}`)
})