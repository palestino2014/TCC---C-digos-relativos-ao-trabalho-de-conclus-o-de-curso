echo -e "sou uma linha\nsou outra linha\nesta linha tem número 1\nesta já não tem número" | sed -r '/[0-9]+/ a Oi. Sou novo aqui'
