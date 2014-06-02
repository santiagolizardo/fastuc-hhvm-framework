<?hh // strict
namespace Fastuc\Db\Sql;

class InsertBuilder extends BaseBuilder
{
	/**
	 * @var array
	 */
	private array $values;

	public function __construct( string $tableName = null )
	{
		parent::__construct( $tableName );

		$this->values = array();
	}

	/**
	 * @param mixed $value
	 * @return $this
	 */
	public function addValue( mixed $value ) : this
	{
		$this->values[] = strval( $value );
		return $this;
	}

	/**
	 * @return array
	 */
	public function getValues() : array
	{
		return $this->values;
	}

	/**
	 * @return string
	 */
	public function build() : string
	{
		$sql = array();
	
		$sql[] = 'INSERT INTO';
		$sql[] = $this->tableName;
		$sql[] = '( ' . implode( ', ', $this->columns ) . ' )';
		$sql[] = 'VALUES';
		$sql[] = '( ' . implode( ', ', $this->values ) . ' )';
		
		return implode( ' ', $sql );
	}
}

