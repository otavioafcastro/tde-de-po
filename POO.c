public class Produto Add commentMore actions
{
    public string Id { get; }
    public string Nome { get; }
    public double Preco { get; set; }
    public string Categoria { get; }

    public Produto(string id, string nome, double preco, string categoria)
    {
        if (preco <= 0)
        Console.WriteLine("Preço inválido");
        return;
        Id = id;
        Nome = nome;
        Preco = preco;
        Categoria = categoria;
    }
}
public class Cliente {
    public int Id { get; private set; }
    public string Nome { get; private set; }
    public string Email { get; private set; }
    public string Cpf { get; private set; }

    public Cliente(int id, string nome, string email, string cpf) {
        Id = id;
        Nome = nome;
        Email = email;
        Cpf = cpf;
    }
}
public class ItemPedido {
    public Produto Produto { get; private set; }
    public int Quantidade { get; private set; }

    public ItemPedido(Produto produto, int quantidade) {
        Produto = produto;
        Quantidade = quantidade;
      
      #Abaixo seria um metódo da classe Item pedido na qual seu objetivo é multiplicar o preço pela quantidade, dando o subtotal do item, por exemplo: Cliente comprou dois mouses no valor de 150 reais, ele irá entender da seguinte forma ( 150 * 2 ) e irá retornar o subtotal.
   
    }
    
    public decimal Subtotal() {
        return Produto.Preco * Quantidade;
    }
}
