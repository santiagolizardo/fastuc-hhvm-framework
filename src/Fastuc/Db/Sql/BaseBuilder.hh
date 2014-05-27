<?hh // strict
namespace Fastuc\Db\Sql;

abstract class BaseBuilder
{
	/**
	 * @var string
	 */
	protected string $tableName;

	/**
	 * @var array
	 */
	protected array $columns;

	/**
	 * @param string|null $tableName
	 */
	public function __construct( string $tableName = null )
	{
		$this->tableName = $tableName;
		$this->columns = array();
	}

	/**
	 * @param string $column
	 * @return $this
	 */
	public function addColumn( string $column ) : this
	{
		$this->columns[] = strval( $column );
		return $this;
	}

	/**
	 * @return $this
	 */
	public function addColumns( ...$columns ) : this
	{
		foreach( $columns as $column )
		{
			$this->addColumn( $column );
		}
		return $this;
	}

	/**
	 * @return array
	 */
	public function getColumns() : array
	{
		return $this->columns;
	}

	/**
	 * @param string $tableName
	 * @return $this
	 */
	public function setTableName( string $tableName ) : this
	{
		$this->tableName = $tableName;
		return $this;
	}

	/**
	 * @return string
	 */
	public function getTableName() : string
	{
		return $this->tableName;
	}

	/**
	 * @return string
	 */
	public abstract function build() : string;
}

