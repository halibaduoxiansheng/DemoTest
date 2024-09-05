import openai, os
# 现在需要的就只是需要一个可以连接外网的东西了
start_sequence = "\nA:"
restart_sequence = "Q: "
# Replace `<your_api_key>` with your actual OpenAI API key
openai.api_key = "<your_api_key>"
prompt = " "
while len(prompt) != 0:
    # Ask a question
    prompt = input(restart_sequence)
    # prompt = "tell me in Chinese:" + input("\n请输入要翻译的内容：")

    # Get my answer
    response = openai.Completion.create(
        engine="text-davinci-003",
        prompt=prompt,
        temperature=1,
        max_tokens=2000,
        frequency_penalty=0,
        presence_penalty=0
    )

    # Print my answer
    print(start_sequence,response["choices"][0]["text"].strip())