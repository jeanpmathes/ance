std::string ance::est::RunnableDeclaration::displayName() const
{
    return "runnable";
}

std::string ance::est::NameDeclaration::displayName() const
{
    return std::string(identifier.text());
}

bool ance::est::Statement::isCompound() const
{
    return false;
}

bool ance::est::Block::isCompound() const
{
    return true;
}
