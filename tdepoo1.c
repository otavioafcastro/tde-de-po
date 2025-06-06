class Produto
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
