bool ance::ast::Statement::isCompound() const
{
    return false;
}

bool ance::ast::Block::isCompound() const
{
    return true;
}
