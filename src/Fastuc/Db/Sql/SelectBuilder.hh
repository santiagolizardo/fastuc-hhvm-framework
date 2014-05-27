<?hh // strict
namespace Fastuc\Db\Sql;

class SelectBuilder extends BaseBuilder
{
	/**
	 * @var array
	 */
	private array $joins;

	/**
	 * @var array
	 */
	private array $whereConditions;

	/**
	 * @var integer
	 */
	private int $offset;

	/**
	 * @var integer
	 */
	private int $limit;

	/**
	 * @var string
	 */
	private string $orderBy;

	/**
	 * @param string $tableName
	 */
	public function __construct( string $tableName = null )
	{
		parent::__construct( $tableName );

		$this->joins = array();
		$this->whereConditions = array();
		$this->offset = null;
		$this->limit = 10;
		$this->orderBy = null;
	}

	/**
	 * @param string $join
	 * @return $this
	 */
	public function addJoin( string $join ) : this
	{
		$this->joins[] = $join;
		return $this;
	}

	/**
	 * @param string $orderBy
	 * @return $this
	 */
	public function setOrderBy( string $orderBy ) : this
	{
		$this->orderBy = $orderBy;
		return $this;
	}

	/**
	 * @param string $whereCondition
	 * @return $this
	 */
	public function addWhere( string $whereCondition ) : this
	{
		$this->whereConditions[] = $whereCondition;
		return $this;
	}

	/**
	 * @param integer $offset
	 * @param integer $limit
	 * @return $this
	 */
	public function setOffsetLimit( int $offset, int $limit ) : this
	{
		$this->offset = $offset;
		$this->limit = $limit;
		return $this;
	}

	/**
	 * @return string
	 */
	public function build() : string
	{
		$sql = array();

		$sql[] = 'SELECT';

		if( count( $this->columns ) == 0 )
		{
			$sql[] = '*';
		}
		else
		{
			$sql[] = implode( ', ', $this->columns );
		}

		$sql[] = 'FROM';
		$sql[] = $this->tableName;

		if( count( $this->joins ) > 0 )
		{
			$sql[] = implode( ' ', $this->joins );
		}

		if( count( $this->whereConditions ) > 0 )
		{
			$sql[] = 'WHERE';
			$sql[] = implode( ' AND ', $this->whereConditions );
		}

		if( $this->orderBy != null )
		{
			$sql[] = 'ORDER BY ' . $this->orderBy;
		}

		if( null !== $this->offset )
		{
			$sql[] = 'LIMIT ' . $this->offset . ', ' . $this->limit;
		}

		return implode( ' ', $sql );
	}
}

